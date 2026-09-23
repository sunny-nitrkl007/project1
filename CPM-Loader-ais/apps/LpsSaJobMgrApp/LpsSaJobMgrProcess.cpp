/*******************************************************************************
** COPYRIGHT (C) 2016-2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsSaJobMgrProcess.cpp
DESCRIPTION:
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdio.h>

#include "LpsSaJobMgrApp.h"
#include <clock_tm_zone_proto.h>
#include <chrono>

#include <chrono/print.hpp>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/


/******************************************************************************
FUNCTION NAME:LpsSaJobMgrPtUpdate
DESCRIPTION: Handles inputs and outputs of PT lib.           
PARAMETER DESCRIPTION:                        
RETURN VALUE:             
*******************************************************************************/
boolean LpsSaJobMgrApp::LpsSaJobMgrPtUpdate(void)
{
    LpsSaJobMgrWmInput.cpm_install_status = true;

    if(LpsJobMgrJobTrackerInfoTbl.CalStat == LPS_WEIGH_SYSTEM_CALIBRATED)
    {
        LpsSaJobMgrWmInput.cpm_is_calibrated = true;
    }

    LpsSaJobMgrWmInput.pt_time_step_us = 100000.00;

    if(LpsJobMgrJobTrackerInfoTbl.DumpStat == LPS_WEIGHT_BKT_PARTIALLY_DUMPED)
    {
        LpsSaJobMgrWmInput.dump_state_is_partial_dump = true;
    }
    else if(LpsJobMgrJobTrackerInfoTbl.DumpStat == LPS_WEIGHT_BKT_FULLY_DUMPED)
    {
        // Full dump is beyond partial dump, therefore partial dump is also true.
        LpsSaJobMgrWmInput.dump_state_is_partial_dump = true;
        LpsSaJobMgrWmInput.dump_state_is_full_dump = true;
    }

    if (LPS_WEIGHT_BKT_DIGGING == LpsJobMgrJobTrackerInfoTbl.DigStat)
    {
        LpsSaJobMgrWmInput.dig_detected = true;
    }

    /* SEA Level2 (Pro) Interlock */
    if (SEALevel2ProInstalled_) {
        LpsSaJobMgrWmInput.manual_add_enabled = config_.manualAddEnabled;
    }
    else {
        /* not installed, disable following Pro features */
        LpsSaJobMgrWmInput.manual_add_enabled = false;
    }

    LpsSaJobMgrWmInput.tip_off_trigger = config_.tipOffTriggerType;

    if (SEALegalForTradeInstalled_) {
        LpsSaJobMgrWmInput.auto_store_enabled = false;
        LpsSaJobMgrWmInput.maximum_pass_count = LPSSAJOBMGRCNFG_AUTO_STORE_PASS_COUNT_MAX;
    }
    else {
        LpsSaJobMgrWmInput.auto_store_enabled = true;
        LpsSaJobMgrWmInput.maximum_pass_count = config_.autoStorePassCount;
    }

    /*
     * Update the Pass Tracker State Machine (weigh_mode)
     *  But not unless we have received input from the weigh app.
     *  We cannot make any assumptions about the inputs from the weigh app
     *  prior to updating pass tracker.  For example, the calibration status is
     *  unknown until we receive it from the weigh app.
     */
    if (weighAppTxDataReceived_) {
        LpsSaJobMgrWmOutput = LpsPtUpdate(&LpsSaJobMgrWmInput);
    }

    /*
     * Handle Load Update
     */
    {
        bool changed = false;

        if (LpsSaJobMgrWmOutput.loadUpdate.addPass) {
            tasks_.currentTaskLoadAddPass(LpsSaJobMgrWmOutput.loadUpdate.addPassWeight,
                    LpsSaJobMgrWmOutput.loadUpdate.addPassAccuracy, serviceHourMeter_);
	        AIS_LOG_NOTICE("Load Change - addPass");
            changed = true;
        }

        if (LpsSaJobMgrWmOutput.loadUpdate.removePass) {
            bool removedPass = tasks_.currentTaskLoadRemoveLastPass(serviceHourMeter_);

            if (removedPass) {
                // restore truck with updated load
                const LpsSaLoadRecordSubtotal& subtotal = tasks_.getCurrentTaskLoad().getCurrentSubtotal();
                LpsWeighBktWtAccuracy_t lastPassAccuracy;
                float lastPassWeight = subtotal.lastPassWeightTonnes(lastPassAccuracy);
                LpsPtRestoreTruck(subtotal.weightTonnes(), subtotal.passCount(), FALSE, lastPassWeight, lastPassAccuracy);
            }
            else {
                LpsSaJobMgrPtRestoreTruck(); // Make sure the information gets reflected in the pass tracker truck
            }

            AIS_LOG_NOTICE("Load Change - removePass");
            changed = true;
        }

        if (LpsSaJobMgrWmOutput.loadUpdate.clear) {
            tasks_.currentTaskLoadClearCurrentSubtotal();
            AIS_LOG_NOTICE("Load Change - clear");
            changed = true;
        }

        // Publish load records on store only if SEA level1 is installed, and if store was not due to split mode
        //  next subtotal cmd or select subtotal cmd
        if (LpsSaJobMgrWmOutput.loadUpdate.store
                && !LpsJobMgrJobTrackerInfoTbl.splitModeNextPayloadCmd
                && !LpsJobMgrJobTrackerInfoTbl.selectSubtotalCmd
                && SEALevel1EssentialsInstalled_) {
            // Honk the horn if it is not an auto store and SEA level2 (Pro) is installed
            if (!LpsSaJobMgrWmOutput.loadUpdate.isAutoStore
                    && SEALevel2ProInstalled_) {
                LpsSaJobMgrScsChkHornAction();
            }

            { // Close out the current tasks load and sent it on to downstream consumers.
                LpsSaLoadRecordChannel loadRecord;

                { // Get load record
                    LpsSaLoadRecordChannelStorage& loadRecordData = loadRecord;
                    loadRecordData = tasks_.currentTaskLoadClose(serviceHourMeter_);
                }

                if (loadRecord.passCount() > 0) {
                    { // remove subtotals with zero passes
                        // looping backwards from the end so we can remove items along the way without
                        //  ruining the indexing.
                        for (auto idx = loadRecord.subtotalCount(); idx > 0; idx--) {
                            if (0 == loadRecord.getSubtotalByIndex(idx).passCount()) {
                                // remove subtotal
                                loadRecord.removeSubtotal(idx);
                            }
                        }
                    }

                    LpsJobMgrJobTrackerInfoTbl.storePressCount++;

                    // Set the reason for store.
                    if (LpsSaJobMgrWmOutput.loadUpdate.isAutoStore) {
                        loadRecord.storeAction(LpsSaLoadRecordStoreAction::AUTO);
                    }
                    else if (SEALegalForTradeInstalled_) {
                        // If nobody disabled LFT, then it is LFT
                        if (loadRecord.storeAction() != LpsSaLoadRecordStoreAction::TICKET_NOT_FOR_TRADE) {
                            loadRecord.storeAction(LpsSaLoadRecordStoreAction::TICKET_LEGAL_FOR_TRADE);
                        }
                    }
                    else {
                        loadRecord.storeAction(LpsSaLoadRecordStoreAction::TICKET_NOT_FOR_TRADE);
                    }

                    // disable lists if SEA Level2 is not installed
                    if (!SEALevel2ProInstalled_) {
                        loadRecord.disableLists();
                    }

                    /*
                     * If user tags are not enabled, then clear them out of the published
                     * load record.  This means that the last set values for these tags
                     * will be retained if the tags get enabled again.  We need to clear
                     * them out here so that we don't have incorrect "orphaned" tags
                     * sent to the back office and/or accumulated in totals.
                     */

                    if (!config_.truckListEnabled) {
                        loadRecord.disableTruckList();
                    }

                    if (!config_.materialListEnabled) {
                        loadRecord.disableMaterialList();
                    }

                    if (!config_.tag1Enabled) {
                        loadRecord.disableTag1List();
                    }

                    if (!config_.tag2Enabled) {
                        loadRecord.disableTag2List();
                    }

                    if (!config_.tag3Enabled) {
                        loadRecord.disableTag3List();
                    }

                    if (!config_.tag4Enabled) {
                        loadRecord.disableTag4List();
                    }

                    // set zero/cal adjust for last subtotal
                    loadRecord.getCurrentSubtotal().setZeroWeight(LpsJobMgrJobTrackerInfoTbl.zeroWeight);
                    loadRecord.getCurrentSubtotal().setSimpleCalAdjust(LpsJobMgrJobTrackerInfoTbl.simpleCalAdjust);

                    // Add load to simple cal
                    simpleCal_.addEntry(loadRecord);

                    // Publish the load record (ROS2 only; bridge forwards to AIS-SCS consumers)
                    if (nullptr != loadRecordOutputChannel_) {
                        loadRecordOutputChannel_->publish(convertLoadRecordToRos(loadRecord));
                    }
                }
            }

            AIS_LOG_NOTICE("Load Change - store");
            changed = true;
        }

        if (LpsJobMgrJobTrackerInfoTbl.splitModeNextPayloadCmd) {
            LpsSaLoadRecordChannelStorage& load = tasks_.getCurrentTaskLoad();
            LpsSaLoadRecordSubtotal& subtotal = load.getCurrentSubtotal();

            // set the zero and cal adjust for subtotal being closed out
            subtotal.setZeroWeight(LpsJobMgrJobTrackerInfoTbl.zeroWeight);
            subtotal.setSimpleCalAdjust(LpsJobMgrJobTrackerInfoTbl.simpleCalAdjust);

            // add new subtotal
            load.nextSubtotal(serviceHourMeter_);

            LpsSaJobMgrPtRestoreTruck(); // Make sure the information gets reflected in the pass tracker truck

            //reset command
            LpsJobMgrJobTrackerInfoTbl.splitModeNextPayloadCmd = false;

            AIS_LOG_NOTICE("Load Change - next payload subtotal");
            changed = true;
        }

        if (LpsJobMgrJobTrackerInfoTbl.selectSubtotalCmd) {
            LpsSaLoadRecordChannelStorage& load = tasks_.getCurrentTaskLoad();
            LpsSaLoadRecordSubtotal& subtotal = load.getCurrentSubtotal();

            // set the zero and cal adjust for subtotal being closed out
            subtotal.setZeroWeight(LpsJobMgrJobTrackerInfoTbl.zeroWeight);
            subtotal.setSimpleCalAdjust(LpsJobMgrJobTrackerInfoTbl.simpleCalAdjust);

            // select subtotal
            load.selectSubtotal(serviceHourMeter_, LpsJobMgrJobTrackerInfoTbl.subtotalIndex);

            LpsSaJobMgrPtRestoreTruck(); // Make sure the information gets reflected in the pass tracker truck

            //reset command
            LpsJobMgrJobTrackerInfoTbl.selectSubtotalCmd = false;

            AIS_LOG_NOTICE("Load Change - select subtotal");
            changed = true;
        }

        if (changed) {
            tasks_.save();
        }
    }

    // Payload Operating Mode (D10748)
    if(!LpsSaJobMgrWmInput.cpm_is_calibrated) {
        LpsJobMgrJobTrackerInfoTbl.OperationMode = LPS_SA_JOB_MGR_UNCALIBRATED; // Not calibrated
    }
    else if (LpsSaJobMgrWmOutput.standby_active) {
        LpsJobMgrJobTrackerInfoTbl.OperationMode = LPS_SA_JOB_MGR_STANDBY_MODE;  // In Standby
    }
    else if (LpsSaJobMgrWmOutput.tip_off_active) {
        LpsJobMgrJobTrackerInfoTbl.OperationMode = LPS_SA_JOB_MGR_EXCESS_MODE;   // In tip off
    }
    else {
        LpsJobMgrJobTrackerInfoTbl.OperationMode = LPS_SA_JOB_MGR_WEIGH_MODE;   // Normal mode
    }

    LpsJobMgrJobTrackerInfoTbl.ReqPloadCtrlSysStat = GetActiveButtonStatus();

    LpsJobMgrJobTrackerInfoTbl.DispBestBktWt.val = LpsSaJobMgrWmOutput.display_bucket_weight;

    LpsSaJobMgrSendCmdToWeighApp();

    resetLpsPtInputFlags();   // Reset the flags and then handle tipoff.

    // Did tip-off assist become active or inactive like requested?
    if (!LpsSaJobMgrWmOutput.tip_off_active) {
        // If we are not in tip-off, we are definitely not in tip-off assist
        LpsJobMgrJobTrackerInfoTbl.TipoffAssistActive = false;
    }
    else if (LpsJobMgrJobTrackerInfoTbl.TipoffAssistPIDActive != LpsJobMgrJobTrackerInfoTbl.TipoffAssistActive) {
        // This is the result of the request to enter or exit tip-off.
        LpsJobMgrJobTrackerInfoTbl.TipoffAssistActive = LpsSaJobMgrWmOutput.tip_off_active;
    }

    LpsSaJobMgrHandleTipOffBtnStates();

    //Set flags to show bucket weight on the display.
    if (TRUE == LpsSaJobMgrWmOutput.display_bucket_weight_available)
    {
        LpsJobMgrJobTrackerInfoTbl.DispBestBktWt.isOk = true;
    }
    else
    {
        /* Sending display status to UI to display *** at Bucket weight */
        LpsJobMgrJobTrackerInfoTbl.DispBestBktWt.isOk = false;
    }

    return SUCCESS;
}


/******************************************************************************
FUNCTION: LpsSaJobMgrScsChkHornAction
DESCRIPTION: Raise Action Flag when it fit the condition.
PARAMETER DESCRIPTION:
RETURN VALUE:void
*******************************************************************************/
void LpsSaJobMgrApp::LpsSaJobMgrScsChkHornAction()
{
    if (config_.hornStoreEnable) {
        AIS_LOG_INFO("Horn: ACTIVACTED");
        LpsSaJobMgrHornOnStoreAction(); // send scs object to OutputApp to drive Output Pin
    }
    else {
        AIS_LOG_INFO("Horn: NOT ACTIVATED");
    }
}


/******************************************************************************
FUNCTION:LpsSaJobMgrHandleTipOffBtnStates
DESCRIPTION:Handles whether to show or hide tip off buttons.
PARAMETER DESCRIPTION:
RETURN VALUE:void
*******************************************************************************/
void LpsSaJobMgrApp::LpsSaJobMgrHandleTipOffBtnStates()
{
    LpsJobMgrJobTrackerInfoTbl.TipOffState = LPS_SA_JOB_MGR_TIP_OFF_UNAVAILABLE;
    LpsJobMgrJobTrackerInfoTbl.ManualTipOffState = LPS_SA_JOB_MGR_MAN_TIP_OFF_UNAVAILABLE;

    // Tip Off manual
    if (LpsSaJobMgrWmInput.tip_off_trigger == TIP_OFF_TRIGGER_MANUAL)
    {
    	if (LpsSaJobMgrWmOutput.tip_off_active)
    	{
    		LpsJobMgrJobTrackerInfoTbl.ManualTipOffState = LPS_SA_JOB_MGR_MAN_TIP_OFF_ACTIVE;
    	}
    	else if (LpsSaJobMgrWmOutput.display_bucket_weight_available)
    	{
    		LpsJobMgrJobTrackerInfoTbl.ManualTipOffState = LPS_SA_JOB_MGR_MAN_TIP_OFF_AVAILABLE;
    	}
    	else {
    		LpsJobMgrJobTrackerInfoTbl.ManualTipOffState = LPS_SA_JOB_MGR_MAN_TIP_OFF_UNAVAILABLE;
    	}
    }
    else {
    	LpsJobMgrJobTrackerInfoTbl.ManualTipOffState = LPS_SA_JOB_MGR_MAN_TIP_OFF_UNAVAILABLE;
    }
    // Tip Off Auto or Disabled or Tipoff Assist is Active
    if (LpsSaJobMgrWmOutput.tip_off_active && (!LpsJobMgrJobTrackerInfoTbl.TipoffAssistActive))
    {
    	LpsJobMgrJobTrackerInfoTbl.TipOffState = (LpsSaJobMgrTipOffState_t)LpsSaJobMgrWmOutput.tip_off_mode;
    }
    else {
    	LpsJobMgrJobTrackerInfoTbl.TipOffState = LPS_SA_JOB_MGR_TIP_OFF_UNAVAILABLE;

    }
}

/******************************************************************************
FUNCTION:LpsSaJobMgrSendCmdToWeighApp
DESCRIPTION:Send appropriate commands to weigh app depending on flags set. 
PARAMETER DESCRIPTION:
RETURN VALUE:void
*******************************************************************************/
void LpsSaJobMgrApp::LpsSaJobMgrSendCmdToWeighApp()
{
    if (LpsSaJobMgrWmOutput.unlatch_current_bucket_weight) {
        LpsSaJobMgrScsSendCmd(LpsSaWeighReqstChannel::Command::RESET_BEST_BUCKET_WEIGHT);
    }

    if (LpsSaJobMgrWmOutput.dump_detect_capture_cyl_ext_reference) {
        LpsSaJobMgrScsSendCmd(LpsSaWeighReqstChannel::Command::CAPTURE_CYLINDER_EXTENSION_REFERENCE);
    }

    if (LpsSaJobMgrWmOutput.clear_reweigh_warning_status) {
        LpsSaJobMgrScsSendCmd(LpsSaWeighReqstChannel::Command::CLEAR_REWEIGH_WARNING);
    }
}

/******************************************************************************
FUNCTION NAME: LpsSaJobMgrApp::convertLoadRecordToRos
DESCRIPTION: Converts LpsSaLoadRecordChannelStorage (AIS SCS Datum<>) to
    job_mgr_interfaces::msg::LpsSaLoadRecordChannel (ROS2) for publication.
    Field-by-field mapping verified against:
      prod/common/interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h
      prod/common/interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordSubtotal.h
      ros2_model/src/job_mgr_interfaces/msg/LpsSaLoadRecordChannel.msg (+ nested .msg)
    Access pattern: uses only public accessors (subtotalCount, getSubtotalByIndex,
    passes()) to avoid depending on private friendship -- no private member access.
*******************************************************************************/
/*static*/ job_mgr_interfaces::msg::LpsSaLoadRecordChannel
LpsSaJobMgrApp::convertLoadRecordToRos(const LpsSaLoadRecordChannel& scs)
{
    job_mgr_interfaces::msg::LpsSaLoadRecordChannel ros;

    ros.store_action = LpsSaLoadRecordStoreAction_Base_t(scs.storeAction());

    ros.ticket_number = scs.ticketNumber();
    ros.ticket_id     = scs.ticketId();

    ros.product_id             = scs.productId();
    ros.equipment_id           = scs.equipmentId();
    ros.weight_interval        = scs.weightInterval();
    ros.weight_decimal_precision = scs.weightDecimalPrecision();
    ros.weight_units           = static_cast<int32_t>(LpsCommonWeightUnits_Base_t(scs.weightUnits()));

    ros.recipe_name            = scs.recipeName();
    ros.target_type            = static_cast<uint8_t>(scs.targetType());
    ros.total_target_weight    = scs.getTotalTargetWeight();
    ros.current_subtotal_index = scs.getCurrentSubtotalIndex();

    ros.store_time.utc_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
            scs.storeTime.utcTime.time_since_epoch()).count();
    ros.store_time.shm_time    = scs.storeTime.shmTime;

    /* Convert subtotals -- index 1 is the "primary" subtotal (subtotal_),
       indices 2..N are the additional ones (subtotals_).
       Public API: subtotalCount() and getSubtotalByIndex(1-based). */
    auto convertSubtotal = [](const LpsSaLoadRecordSubtotal& s)
            -> job_mgr_interfaces::msg::LoadRecordSubtotal
    {
        job_mgr_interfaces::msg::LoadRecordSubtotal rs;

        rs.start_time.utc_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                s.startTime.utcTime.time_since_epoch()).count();
        rs.start_time.shm_time    = s.startTime.shmTime;
        rs.end_time.utc_time_ns   = std::chrono::duration_cast<std::chrono::nanoseconds>(
                s.endTime.utcTime.time_since_epoch()).count();
        rs.end_time.shm_time      = s.endTime.shmTime;

        rs.truck_id                   = s.truckId;
        rs.truck_name                 = s.truckName;
        rs.truck_target_weight_tonnes = s.truckTargetWeightTonnes;
        rs.target_proportion          = s.targetProportion;
        rs.target_passes              = s.targetPasses;
        rs.material_id                = s.materialId;
        rs.material_name              = s.materialName;
        rs.material_density           = s.materialDensity;
        rs.custom_list_name1          = s.customListName1;
        rs.custom_list_name2          = s.customListName2;
        rs.custom_list_name3          = s.customListName3;
        rs.custom_list_name4          = s.customListName4;
        rs.tag1                       = s.tag1;
        rs.tag2                       = s.tag2;
        rs.tag3                       = s.tag3;
        rs.tag4                       = s.tag4;
        rs.icon_type                  = s.iconType;
        rs.zero_weight                = s.zeroWeight;
        rs.cal_adjust                 = s.calAdjust;

        LpsWeighBktWtAccuracy_t acc;
        rs.weight_tonnes = s.weightTonnes(acc);
        rs.accuracy.value = static_cast<uint8_t>(acc);

        rs.passes.reserve(s.passes().size());
        for (const auto& p : s.passes()) {
            job_mgr_interfaces::msg::LoadRecordPass rp;
            rp.weight_tonnes = p.weightTonnes;
            rp.calc_method   = p.calcMethod;
            rp.time.utc_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    p.time.utcTime.time_since_epoch()).count();
            rp.time.shm_time = p.time.shmTime;
            rs.passes.push_back(rp);
        }

        return rs;
    };

    uint32_t count = scs.subtotalCount();
    for (uint16_t i = 1; i <= count; ++i) {
        const LpsSaLoadRecordSubtotal& sub = scs.getSubtotalByIndex(i);
        if (i == 1) {
            ros.subtotal = convertSubtotal(sub);
        } else {
            ros.subtotals.push_back(convertSubtotal(sub));
        }
    }

    return ros;
}

job_mgr_interfaces::msg::LpsSaJobMgrTxChannel LpsSaJobMgrApp::convertJobMgrTxToRos(const LpsSaJobMgrTxChannel& scs)
{
    job_mgr_interfaces::msg::LpsSaJobMgrTxChannel ros;
    ros.time_point_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(scs.timePoint.time_since_epoch()).count();
    ros.task_number = scs.taskNumber; ros.pass_count = scs.passCount; ros.truck_weight = scs.truckWeight;
    ros.truck_weight_accuracy.value = static_cast<uint8_t>(scs.truckWeightAccuracy); ros.truck_start_weight = scs.TruckStartWeight;
    ros.remaining_weight = scs.remainingWeight; ros.total_weight = scs.totalWeight;
    ros.total_weight_accuracy.value = static_cast<uint8_t>(scs.totalWeightAccuracy); ros.subtotal_count = scs.subtotalCount;
    ros.ticket_id = scs.ticketId; ros.material_id = scs.materialId; ros.material_name = scs.materialName;
    ros.material_density = scs.materialDensity; ros.truck_id = scs.truckId; ros.truck_name = scs.truckName;
    ros.truck_target_weight = scs.truckTargetWeight; ros.truck_list_enabled = scs.truckListEnabled;
    ros.material_list_enabled = scs.materialListEnabled; ros.tag1_enabled = scs.tag1Enabled;
    ros.custom_list_name1 = scs.customListName1; ros.tag1 = scs.tag1; ros.tag2_enabled = scs.tag2Enabled;
    ros.custom_list_name2 = scs.customListName2; ros.tag2 = scs.tag2; ros.tag3_enabled = scs.tag3Enabled;
    ros.custom_list_name3 = scs.customListName3; ros.tag3 = scs.tag3; ros.tag4_enabled = scs.tag4Enabled;
    ros.custom_list_name4 = scs.customListName4; ros.tag4 = scs.tag4; ros.manual_tip_off_state = static_cast<uint8_t>(scs.ManualTipOffState);
    ros.tip_off_trigger_type.value = static_cast<uint8_t>(scs.TipOffTriggerType); ros.tip_off_state.value = static_cast<uint8_t>(scs.TipOffState);
    ros.tip_off_state_cfg.value = static_cast<uint8_t>(scs.TipOffStateCfg); ros.operation_mode = static_cast<uint16_t>(scs.OperationMode);
    ros.standby_state.value = static_cast<uint8_t>(scs.StandbyState); ros.clear_minus_one_enable_stat = static_cast<uint8_t>(scs.ClearMinusOneEnableStat);
    ros.disp_best_bkt_wt.val = scs.DispBestBktWt.val; ros.disp_best_bkt_wt.is_ok = scs.DispBestBktWt.isOk;
    for (const auto& data : scs.simpleCalData) { job_mgr_interfaces::msg::SimpleCalData entry; entry.time_stamp = data.timeStamp; entry.truck_wt = data.truckWt; entry.zeroed_truck_wt = data.zeroedTruckWt; ros.simple_cal_data.push_back(entry); }
    ros.store_count = scs.storeCount; ros.store_rejected = scs.storeRejected; ros.req_pload_ctrl_sys_stat = static_cast<uint16_t>(scs.ReqPloadCtrlSysStat);
    ros.horn_store_state = static_cast<uint16_t>(scs.HornStoreState); ros.auto_store_pass_count = scs.AutoStorePassCount;
    ros.auto_truck_id_enabled = scs.AutoTruckIdEnabled; ros.auto_material_id_enabled = scs.AutoMaterialIdEnabled;
    ros.manual_add_enabled = scs.manualAddEnabled; ros.multi_task_enabled = scs.multiTaskEnabled; ros.multi_task_count = scs.multiTaskCount;
    ros.tipoff_active = scs.TipoffActive; ros.tipoff_assist_active = scs.tipoffAssistActive; ros.tipoff_assist_active_eid = scs.tipoffAssistActiveEid;
    ros.manual_add_available = scs.manualAddAvailable; ros.split_mode_enabled = scs.splitModeEnabled; ros.lft_disabled = scs.lftDisabled;
    ros.target_type = scs.targetType; ros.step_number = scs.stepNumber; ros.icon_type = scs.iconType; ros.target_passes = scs.targetPasses;
    return ros;
}
