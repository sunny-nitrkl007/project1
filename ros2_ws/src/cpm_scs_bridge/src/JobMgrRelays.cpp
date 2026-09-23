/*******************************************************************************
FILE NAME: JobMgrRelays.cpp
DESCRIPTION:
    One relay method per JobMgr bridge leg (Development-Plan.txt Step 7.1's
    13-leg list), called once per tick from CpmScsBridgeApp::executive().

    Status of this pass: 5 of 13 legs are implemented end-to-end
    (relayJobMgrRespChannel, relaySwitchInputScs, relayJobMgrTxChannel,
    relayAisJhm2TxChannel, and relayOutputChannel -- the last with an
    already-precedented unverified-placeholder gap on its SCS write side,
    same class of gap as LpsSaJobMgrHornOnStoreAction() in the working
    copy). The remaining 8 are real, uncollapsed TODOs -- every one of them
    needs either a large accessor-based field mapping (the pre-conversion
    baseline at git commit cad392b shows the real SCS-side accessor calls
    for most of them) or a real struct header this checkout doesn't have
    (ShmClock.h, DataLinkData.h, EventDiagnosticData.h,
    LpsSaUIDisplayState.h, AutonomyConditionDiagnosticsTxChannel.h are all
    confirmed absent from every checkout under D:\ROS2_Service_Discovery,
    even after TES-common-ais was sourced -- see Challenges-And-Decisions.txt
    3.3. SwitchInputScs and OutputChannel WERE this same class of gap, but
    are no longer -- TES-common-ais resolved both real structs; see
    relaySwitchInputScs()/relayOutputChannel() below). Each stub documents
    exactly which baseline function to pull the real field-access pattern from.
    LpsSaLoadRecordChannel.h (913 lines) IS present but is accessor/getter-
    only from what's been read so far -- no setter API confirmed, so
    relayLoadRecordChannel() is deliberately still a TODO rather than a
    guess at mutator names.
*******************************************************************************/
#include "cpm_scs_bridge/CpmScsBridgeApp.h"

#include <ais/AisLog.h>

#include <chrono>

/******************************************************************************
FUNCTION NAME: CpmScsBridgeApp::relayJobMgrRespChannel
DESCRIPTION:
    Publisher relay (ROS2 -> SCS). JobMgr's own sendReqstResponse()
    (CPM-Loader-ais/apps/LpsSaJobMgrApp/LpsSaJobMgrScs.cpp:644) already
    publishes job_mgr_interfaces::msg::LpsSaJobMgrRespChannel onto this
    topic for DDS-side consumers (WeighApp doesn't read it -- this is
    purely for the legacy UI). This is a straight field-for-field copy
    onto the real SCS LpsSaJobMgrRespChannelOutput -- the real struct
    (prod/common/interfaces/LpsSaJobMgrRespChannel/LpsSaJobMgrRespChannel.h)
    is a plain Datum<LpsSaJobMgrRespChannelStorage> with the same 5 fields
    the pre-conversion baseline's sendReqstResponse() (git commit cad392b,
    LpsSaJobMgrScs.cpp:621) used verbatim.
*******************************************************************************/
void CpmScsBridgeApp::relayJobMgrRespChannel()
{
    if (nullptr == jobMgrRespScsOut_) {
        return;
    }

    job_mgr_interfaces::msg::LpsSaJobMgrRespChannel resp;
    while (jobMgrRespIn_->get(resp)) {
        LpsSaJobMgrRespChannel scsResp; // default timePoint is now, overwritten below
        scsResp.appName = resp.app_name;
        scsResp.appRequestId = resp.app_request_id;
        scsResp.timePoint = std::chrono::steady_clock::time_point(
            std::chrono::duration_cast<std::chrono::steady_clock::duration>(
                std::chrono::nanoseconds(resp.time_point_ns)));
        scsResp.command = static_cast<LpsSaJobMgrReqstChannel::Command>(resp.command.value);
        scsResp.success = resp.success;

        jobMgrRespScsOut_->publish(scsResp);
    }
}

/******************************************************************************
FUNCTION NAME: CpmScsBridgeApp::relaySwitchInputScs
DESCRIPTION:
    Subscriber relay (SCS -> ROS2). job_mgr_interfaces::msg::SwitchInputScs
    now carries the real struct's full shape (TES-common-ais/prod/common/
    interfaces/SwitchInputScs/SwitchInputScs.h): int STG_values[4]
    (NO_OF_STG_INPUTS), STG enum OPEN=0/CLOSED=1/UNKNOWN=2. Relays all 4
    real indices via get_STG_value(int) -- not just STG4/index 3, since
    the Bridge is the one real place this channel needs the full struct
    (unlike JobMgr's own read side, LpsSaJobMgrScs.cpp, which still only
    ever consumes index STG4).
*******************************************************************************/
void CpmScsBridgeApp::relaySwitchInputScs()
{
    if (nullptr == switchInputScsIn_) {
        return;
    }

    SwitchInputScs scsIn;
    while (switchInputScsIn_->get(scsIn)) {
        job_mgr_interfaces::msg::SwitchInputScs msg;
        for (int i = 0; i < NO_OF_STG_INPUTS; ++i) {
            msg.stg_values[i].value = static_cast<uint8_t>(scsIn.get_STG_value(i));
        }
        switchInputOut_->publish(msg);
    }
}

/******************************************************************************
FUNCTION NAME: CpmScsBridgeApp::relayOutputChannel
DESCRIPTION:
    Publisher relay (ROS2 -> SCS). job_mgr_interfaces::msg::OutputChannel's
    DDS side is fully known (job_mgr_interfaces/msg/OutputChannel.msg +
    OutputCmd.msg: commands[], each output_port/initial_state/
    state_change_duration/final_state/total_duration). Real SCS struct
    now sourced: TES-common-ais/prod/common/interfaces/OutputChannel/
    OutputChannel.h -- OutputChannelStorage is a plain
    std::vector<OutputCmd> behind AddOutputAppCmd()/ClearOutputAppCmds(),
    not accessor-gated. Port/State/ChangeDuration are the same enums
    already confirmed and applied to LpsSaJobMgrHornOnStoreAction()'s
    sentinels in the working copy's LpsSaJobMgrScs.cpp (OUTPUT_SINK_3=2,
    PORT_ON=1/PORT_OFF=0, NO_FLASH=0) -- the .msg fields carry the same
    raw integer values either way, so a plain static_cast is all that's
    needed to cross back to the real enum types.
*******************************************************************************/
void CpmScsBridgeApp::relayOutputChannel()
{
    if (nullptr == outputChannelScsOut_) {
        return;
    }

    job_mgr_interfaces::msg::OutputChannel outputChannel;
    while (outputChannelIn_->get(outputChannel)) {
        OutputChannel scsOut;
        for (const auto& cmd : outputChannel.commands) {
            OutputChannel::OutputCmd scsCmd;
            scsCmd.OutputPort = static_cast<OutputChannel::Port>(cmd.output_port);
            scsCmd.InitialState = static_cast<OutputChannel::State>(cmd.initial_state);
            scsCmd.StateChangeDuration = static_cast<OutputChannel::ChangeDuration>(cmd.state_change_duration);
            scsCmd.TotalDuration = cmd.total_duration;
            scsCmd.FinalState = static_cast<OutputChannel::State>(cmd.final_state);
            scsOut.AddOutputAppCmd(scsCmd);
        }
        outputChannelScsOut_->publish(scsOut);
    }
}

/* ---- Remaining 10 legs: real, uncollapsed TODOs. Not stubbed as no-ops -- */
/* ---- left undefined-but-declared would be a link error, so each is a    */
/* ---- clearly-marked pass-through-nothing placeholder, matching the      */
/* ---- honest-gap convention used throughout this codebase.               */

/******************************************************************************
FUNCTION NAME: CpmScsBridgeApp::relayJobMgrTxChannel
DESCRIPTION:
    Publisher relay (ROS2 -> SCS). JobMgr's own already-converted code
    publishes job_mgr_interfaces::msg::LpsSaJobMgrTxChannel onto this
    topic; this is the inverse of that channel's field layout (real struct:
    prod/common/interfaces/LpsSaJobMgrTxChannel/LpsSaJobMgrTxChannel.h,
    a plain-field Datum<LpsSaJobMgrTxChannelStorage>, not accessor-gated --
    confirmed by direct read this session). Field-for-field, cross-checked
    against job_mgr_interfaces/msg/LpsSaJobMgrTxChannel.msg +
    SimpleCalData.msg + WeighBktWtAccuracy.msg + DispBestBktWt.msg +
    TipOffTriggerType.msg + TipOffState.msg + StandbyState.msg directly.
*******************************************************************************/
void CpmScsBridgeApp::relayJobMgrTxChannel()
{
    if (nullptr == jobMgrTxScsOut_) {
        return;
    }

    job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg;
    while (jobMgrTxIn_->get(msg)) {
        LpsSaJobMgrTxChannel scsOut;
        scsOut.timePoint = std::chrono::steady_clock::time_point(
            std::chrono::duration_cast<std::chrono::steady_clock::duration>(
                std::chrono::nanoseconds(msg.time_point_ns)));

        scsOut.taskNumber = msg.task_number;
        scsOut.passCount = msg.pass_count;
        scsOut.truckWeight = msg.truck_weight;
        scsOut.truckWeightAccuracy = static_cast<LpsWeighBktWtAccuracy_t>(msg.truck_weight_accuracy.value);
        scsOut.TruckStartWeight = msg.truck_start_weight;
        scsOut.remainingWeight = msg.remaining_weight;
        scsOut.totalWeight = msg.total_weight;
        scsOut.totalWeightAccuracy = static_cast<LpsWeighBktWtAccuracy_t>(msg.total_weight_accuracy.value);
        scsOut.subtotalCount = msg.subtotal_count;
        scsOut.ticketId = msg.ticket_id;

        scsOut.materialId = msg.material_id;
        scsOut.materialName = msg.material_name;
        scsOut.materialDensity = msg.material_density;

        scsOut.truckId = msg.truck_id;
        scsOut.truckName = msg.truck_name;
        scsOut.truckTargetWeight = msg.truck_target_weight;

        scsOut.truckListEnabled = msg.truck_list_enabled;
        scsOut.materialListEnabled = msg.material_list_enabled;

        scsOut.tag1Enabled = msg.tag1_enabled;
        scsOut.customListName1 = msg.custom_list_name1;
        scsOut.tag1 = msg.tag1;
        scsOut.tag2Enabled = msg.tag2_enabled;
        scsOut.customListName2 = msg.custom_list_name2;
        scsOut.tag2 = msg.tag2;
        scsOut.tag3Enabled = msg.tag3_enabled;
        scsOut.customListName3 = msg.custom_list_name3;
        scsOut.tag3 = msg.tag3;
        scsOut.tag4Enabled = msg.tag4_enabled;
        scsOut.customListName4 = msg.custom_list_name4;
        scsOut.tag4 = msg.tag4;

        scsOut.ManualTipOffState = static_cast<LpsSaJobMgrManualTipOffState_t>(msg.manual_tip_off_state);
        scsOut.TipOffTriggerType = static_cast<LpsSaTipOffTriggerType_t>(msg.tip_off_trigger_type.value);
        scsOut.TipOffState = static_cast<LpsSaJobMgrTipOffState_t>(msg.tip_off_state.value);
        scsOut.OperationMode = static_cast<LpsSaJobMgrOperationMode_t>(msg.operation_mode);
        scsOut.StandbyState = static_cast<LpsSaJobMgrStandbyState_t>(msg.standby_state.value);
        scsOut.ClearMinusOneEnableStat = static_cast<LpsSaJobMgrClearMinusOneEnableStat_t>(msg.clear_minus_one_enable_stat);
        scsOut.DispBestBktWt.val = msg.disp_best_bkt_wt.val;
        scsOut.DispBestBktWt.isOk = msg.disp_best_bkt_wt.is_ok;
        scsOut.TipOffStateCfg = static_cast<LpsSaJobMgrTipOffState_t>(msg.tip_off_state_cfg.value);

        scsOut.simpleCalData.clear();
        for (const auto& cal : msg.simple_cal_data) {
            SimpleCalData_t entry;
            entry.timeStamp = cal.time_stamp;
            entry.truckWt = cal.truck_wt;
            entry.zeroedTruckWt = cal.zeroed_truck_wt;
            scsOut.simpleCalData.push_back(entry);
        }

        scsOut.storeCount = msg.store_count;
        scsOut.storeRejected = msg.store_rejected;
        scsOut.ReqPloadCtrlSysStat = static_cast<ReqPloadCtrlSysStat_t>(msg.req_pload_ctrl_sys_stat);
        scsOut.HornStoreState = static_cast<StorePloadHornStat_t>(msg.horn_store_state);
        scsOut.AutoStorePassCount = msg.auto_store_pass_count;
        scsOut.AutoTruckIdEnabled = msg.auto_truck_id_enabled;
        scsOut.AutoMaterialIdEnabled = msg.auto_material_id_enabled;
        scsOut.manualAddEnabled = msg.manual_add_enabled;
        scsOut.multiTaskEnabled = msg.multi_task_enabled;
        scsOut.multiTaskCount = msg.multi_task_count;
        scsOut.TipoffActive = msg.tipoff_active;
        scsOut.tipoffAssistActive = msg.tipoff_assist_active;
        scsOut.tipoffAssistActiveEid = msg.tipoff_assist_active_eid;
        scsOut.manualAddAvailable = msg.manual_add_available;
        scsOut.splitModeEnabled = msg.split_mode_enabled;
        scsOut.lftDisabled = msg.lft_disabled;
        scsOut.targetType = msg.target_type;
        scsOut.stepNumber = msg.step_number;
        scsOut.iconType = msg.icon_type;
        scsOut.targetPasses = msg.target_passes;

        jobMgrTxScsOut_->publish(scsOut);
    }
}

void CpmScsBridgeApp::relayJobMgrDebugChannel()
{
    // TODO: publisher relay (ROS2->SCS). Real struct present:
    // prod/common/interfaces/LpsSaJobMgrDebugChannel/LpsSaJobMgrDebugChannel.h.
    // ~150 fields -- the largest single channel in either app (see
    // LpsSaWeighApp's LpsSaWeighScsDebugTx() for the sibling channel's
    // already-converted equivalent as a field-count reference point).
    // Deliberately deferred to its own dedicated pass rather than rushed.
}

void CpmScsBridgeApp::relayLoadRecordChannel()
{
    // TODO: publisher relay (ROS2->SCS). Real struct present:
    // prod/common/interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h
    // (913 lines, accessor-heavy, not a plain struct). DDS-side field
    // layout already verified this session against ConvertLoadRecord/
    // ConvertLoadRecordSubtotal/ConvertLoadRecordPass/
    // ConvertLoadRecordTimeStamp in LpsSaJobMgrProcess.cpp:28-124 (the
    // conversion direction those functions do is the one this relay needs
    // to invert).
}

void CpmScsBridgeApp::relayReqstChannel()
{
    // TODO: subscriber relay (SCS->ROS2), legacy/UI leg only -- NOT the
    // same producer as WeighApp's direct DDS leg onto this same topic.
    // Real struct present: prod/common/interfaces/LpsSaJobMgrReqstChannel/
    // LpsSaJobMgrReqstChannel.h. 38 command cases (see
    // cpm_common_interfaces/msg/JobMgrReqstChannelCommand.msg for the
    // full enum) -- the pre-conversion baseline's
    // LpsSaJobMgrScsChkForReqst() (git commit cad392b,
    // LpsSaJobMgrScs.cpp:149-330ish) shows every real accessor call
    // (reqIn.command, reqIn.data.targetType, reqIn.requests[i].command +
    // per-command accessor methods like materialId()/tagName()/tagValue())
    // needed to build the .msg equivalent.
}

/******************************************************************************
FUNCTION NAME: CpmScsBridgeApp::relayAisJhm2TxChannel
DESCRIPTION:
    Subscriber relay (SCS -> ROS2). Real struct (prod/common/interfaces/
    AisJhm2TxChannel/AisJhm2TxChannel.h) is a plain-field
    Datum<AisJhm2TxChannelStorage>, not accessor-gated -- confirmed by
    direct read this session. Field-for-field, cross-checked against
    cpm_common_interfaces/msg/AisJhm2TxChannel.msg + SimpleCalDataT.msg +
    TipoffWeightAdjustData.msg directly (all 10 leaf fields).
*******************************************************************************/
void CpmScsBridgeApp::relayAisJhm2TxChannel()
{
    if (nullptr == aisJhm2TxScsIn_) {
        return;
    }

    AisJhm2TxChannel scsIn;
    while (aisJhm2TxScsIn_->get(scsIn)) {
        cpm_common_interfaces::msg::AisJhm2TxChannel msg;

        msg.simplecal_data.time_stamp = scsIn.simplecal_data.timeStamp;
        msg.simplecal_data.adjtruckweight = scsIn.simplecal_data.adjtruckweight;
        msg.simplecal_data.zeroed_truck_wt = scsIn.simplecal_data.zeroedTruckWt;
        msg.simplecal_data.new_data_flag = scsIn.simplecal_data.newDataFlag;

        msg.tipoff_weight_adjust_data.tip_off_weight1 = scsIn.tipoff_weight_adjust_data.tipOffWeight1;
        msg.tipoff_weight_adjust_data.weigh_range_weight1 = scsIn.tipoff_weight_adjust_data.weighRangeWeight1;
        msg.tipoff_weight_adjust_data.tip_off_weight2 = scsIn.tipoff_weight_adjust_data.tipOffWeight2;
        msg.tipoff_weight_adjust_data.weigh_range_weight2 = scsIn.tipoff_weight_adjust_data.weighRangeWeight2;
        msg.tipoff_weight_adjust_data.new_data_flag = scsIn.tipoff_weight_adjust_data.newDataFlag;
        msg.tipoff_weight_adjust_data.reset = scsIn.tipoff_weight_adjust_data.reset;

        aisJhm2TxOut_->publish(msg);
    }
}

void CpmScsBridgeApp::relayDisplayState()
{
    // TODO: subscriber relay (SCS->ROS2). Real struct
    // (LpsSaUIDisplayState.h) NOT present in this checkout -- only usage
    // via LpsSaUIDisplayStateInterfaceInputChannel's .get() and a nested
    // .state.isInVerificationMode() accessor is known (pre-conversion
    // baseline, LpsSaJobMgrScs.cpp:136-147). DDS side
    // (cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface) was
    // verified this session for both apps -- cross-reference its full
    // field list against whatever real accessors LpsSaUIDisplayState.h
    // exposes once sourced.
}

void CpmScsBridgeApp::relayShmClock()
{
    // TODO: subscriber relay (SCS->ROS2). Real struct (ShmClock.h) NOT
    // present in this checkout. Known real accessors from the pre-
    // conversion baseline's LpsSaJobMgrScsSHMRead() (git commit cad392b,
    // LpsSaJobMgrScs.cpp:726-755): get_UTC_offset(), get_SHM(), and
    // tes_common_ais::get_tz_struct(tzone, shmClock). Cross-reference
    // against cpm_common_interfaces::msg::ShmClockInput's real field list
    // before assuming these 3 are the only ones needed.
}

void CpmScsBridgeApp::relayDataLinkData()
{
    // TODO: subscriber relay (SCS->ROS2). Real struct (DataLinkData.h)
    // NOT present in this checkout. Iterator/accessor-based in the pre-
    // conversion baseline's LpsSaJobMgrScsDataLinkDataRead() (git commit
    // cad392b, LpsSaJobMgrScs.cpp:763+): dlData.GetParams(), per-param
    // IsPIDDataReceived()/GetParamIdentifierType()/GetParamId()/
    // GetLastValueDsi()/GetLastGoodValue<T>(). job_mgr_interfaces::msg::
    // DataLinkData's real field shape needs checking before this can be
    // written with confidence -- likely also a vector-of-params shape,
    // but not yet confirmed against the real .msg this session.
}

void CpmScsBridgeApp::relayAutonomyConditionDiagnosticsTx()
{
    // TODO: subscriber relay (SCS->ROS2). Real struct
    // (AutonomyConditionDiagnosticsTxChannel.h) NOT present in this
    // checkout. DDS side (cpm_common_interfaces::msg::
    // AutonomyConditionDiagnosticsTxChannel) was verified this session
    // (AutonomyConditionDiagnosticsTxChannel/SEA) -- the real SCS-side
    // accessor calls this needs weren't captured from the pre-conversion
    // baseline this session; re-check LpsSaJobMgrApp's executive() in the
    // working copy for the already-converted DDS-side read as a field-
    // list reference, then find the matching pre-conversion accessors.
}

void CpmScsBridgeApp::relayEventDiagnosticData()
{
    // TODO: subscriber relay (SCS->ROS2). Real struct
    // (EventDiagnosticData.h) NOT present in this checkout. Iterator/
    // accessor-based in the pre-conversion baseline's
    // LpsSaJobMgrScsEddtRead() (git commit cad392b,
    // LpsSaJobMgrScs.cpp:663-718): data.getListOfEventDiagnostics(), per-
    // diagnostic diag.category/diag.status/diag.getCID(). DDS side
    // (job_mgr_interfaces::msg::EventDiagnosticData) was verified this
    // session against EventDiagnosticData/Diagnostic.msg -- cross-
    // reference the two before writing this relay.
}
