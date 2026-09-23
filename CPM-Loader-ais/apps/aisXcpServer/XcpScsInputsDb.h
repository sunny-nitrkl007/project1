///////////////////////////////////////////////////////////////////////////////
/// @file      XcpScsInputs.h
/// @author    J Struble
/// @date      3/22/2013
/// @brief     Structure containing all data coming in from SCS that needs
///            to displayed in jhm2
///
/// @attention COPYRIGHT (C) 2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////
#ifndef XCPSCSINPUTS_H_
#define XCPSCSINPUTS_H_

#include <cstdlib>

#include <scsIOContainer/SCSInputs.h>
#include <scsIOContainer/SCSInData.h>
#include <ais/config/ConfigSection.h>

//Interfaces we want to receive and store
#include <ais/interfaces/SystemHardwareHealth/InterfaceTypes.h>
#include <interfaces/LpsSaWeighReqstChannel/InterfaceTypes.h>
#include <interfaces/LpsSaWeighRespChannel/InterfaceTypes.h>
#include <interfaces/LpsSaWeighTxChannel/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrTxChannel/InterfaceTypes.h>
#include <interfaces/PwmInputChannels/InterfaceTypes.h>
#include <interfaces/Machine/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrReqstChannel/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrRespChannel/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrDebugChannel/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrDebugChannel/InterfaceTypes.h>
#include <interfaces/LpsSaWeighDebugChannel/InterfaceTypes.h>
#include <interfaces/LpsSaWeighInitDebugChannel/InterfaceTypes.h>
#include <interfaces/SwitchInputScs/InterfaceTypes.h>
#include <interfaces/LpsSaNvmCalDataChannel/InterfaceTypes.h>
#include <interfaces/LpsSaNvmCalOnTheFlyDataChannel/InterfaceTypes.h>
#include <interfaces/WorkOrderAssist/TxInterfaceInputChannel.h>
#include <interfaces/LpsSaUI/DisplayStateInterfaceInputChannel.h>
#include <interfaces/WidgetsDebugData/InterfaceTypes.h>
#include <interfaces/CycleSeg/TxInterfaceInputChannel.h>
#include <interfaces/TipoffModelTestPoints/InterfaceTypes.h>
#include <interfaces/AutonomyConditionDiagnostics/TxInterfaceInputChannel.h>
#include <interfaces/LpsSaUI/BEMSimStateInterfaceInputChannel.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>

#include <stddef.h>     /* offsetof */
#include "xcp_server/db/XCPServerDb.hpp"
using namespace xcp_server;

// Macros that are used to push SCS data into 'db': DB_PUSH invokes db.update, DB_PUSH_ARRAY expands into a for-loop with DB_PUSH invocations
#define DB_PUSH(item) db.update(groupIdx | offset++, (item))
#define DB_PUSH_ARRAY(array_name,num_elements) for (uint8_t iter=0; iter < num_elements; iter++)                                   \
                                               {                                                                                   \
                                                  DB_PUSH(array_name[iter]);                                                       \
                                               }

class XcpScsInputs : public SCSInputs
{

  public:

    ParameterDb db;

    SCSInData<SystemHardwareHealth> m_systemHardwareHealth;
    SCSInData<LpsSaWeighReqstChannel>   m_lpsSaWeighReqstChannel;
    SCSInData<LpsSaWeighRespChannel>    m_lpsSaWeighRespChannel;
    SCSInData<LpsSaWeighDebugChannel>   m_lpsSaWeighDebugChannel;
    SCSInData<LpsSaWeighInitDebugChannel>    m_lpsSaWeighInitDebugChannel;
    SCSInData<LpsSaWeighTxChannel>       m_lpsSaWeighTxChannel;
    SCSInData<LpsSaNvmCalDataChannel> m_lpsSaNvmDataChannel;
    SCSInData<LpsSaNvmCalOnTheFlyDataChannel> m_lpsSaNvmOnTheFlyDataChannel;
    SCSInData<LpsSaJobMgrTxChannel>       m_lpsSaJobMgrTxChannel;
    SCSInData<PwmInputChannels>           m_pwmInputChannels;
    SCSInData<Machine>                   m_machine;
    SCSInData<LpsSaJobMgrReqstChannel>  m_lpsSaJobMgrReqstChannel;
    SCSInData<LpsSaJobMgrRespChannel>      m_lpsSaJobMgrRespChannel;
    SCSInData<LpsSaJobMgrDebugChannel>  m_lpsSaJobMgrDebugChannel;
    SCSInData<SwitchInputScs>              m_switchInputScs;
    SCSInData<WorkOrderAssistTxInterface> m_workOrderAssistTxChannel;
    SCSInData<LpsSaUIDisplayStateInterface> m_displayStateChannel;
    SCSInData<WidgetsDebugData> m_widgetsDebugdata;
    SCSInData<CycleSegTxInterface> m_cycleSegTxData;
    SCSInData<TipoffModelTestPoints> m_tipoffModelTestPoints;
    SCSInData<AutonomyConditionDiagnosticsTxInterface> m_autonomyConditionDiagnosticsTxChannel;
    SCSInData<LpsSaUIBEMSimStateInterface> m_BemSimDebugChannel;

    DataLinkDataInput* dataLinkDataInput = nullptr;

  ///////////////////////////////////////////////////////////////////////////////
  /// @brief Run "update" on all of the scs channels in the structure
  ///
  /// @return true if any channel has new data, false otherwise
  ///////////////////////////////////////////////////////////////////////////////
  bool update()
  {
    bool retVal = true;
    static bool init_done = false;

    /* index group: 00000 */
    if (m_systemHardwareHealth.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 0;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, false); // Address 0 can't be used
        db.update(groupIdx | offset++, m_systemHardwareHealth.availableSystemMemory_kb);
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.systemUpTime_sec));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.loadAvg1min));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.loadAvg5min));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.loadAvg15min));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.eth0_tx_kbs));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.eth0_rx_kbs));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.eth1_tx_kbs));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.eth1_rx_kbs));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.systemCpuUsage_percent));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.systemCpuIOWait_percent));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.systemCpuIrq_percent));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.battery_voltage));
        db.update(groupIdx | offset++, m_systemHardwareHealth.totalSystemMemory_kb);

        { // Find disk space
            unsigned int avail_kb = 0;
            float percentUse = 100.f;

            for (const auto& diskSpace : m_systemHardwareHealth.listOfRemainingDiskSpace) {
                if (diskSpace.filesystem == "/dev/mmcblk0p2") {
                    avail_kb = diskSpace.avail_kb;
                    percentUse = std::atof(diskSpace.percentUse.c_str());
                    break;
                }
            }

            // Add the channels
            db.update(groupIdx | offset++, avail_kb);
            db.update(groupIdx | offset++, percentUse);
        }

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 10000 */
    if ( m_lpsSaWeighReqstChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 1;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, m_lpsSaWeighReqstChannel.command == LpsSaWeighReqstChannel::Command::ZERO);
        db.update(groupIdx | offset++, m_lpsSaWeighReqstChannel.command == LpsSaWeighReqstChannel::Command::RESET_BEST_BUCKET_WEIGHT);
        db.update(groupIdx | offset++, m_lpsSaWeighReqstChannel.command == LpsSaWeighReqstChannel::Command::CAPTURE_CYLINDER_EXTENSION_REFERENCE);
        db.update(groupIdx | offset++, m_lpsSaWeighReqstChannel.command == LpsSaWeighReqstChannel::Command::WRITE_WEIGH_RANGE);
        db.update(groupIdx | offset++, m_lpsSaWeighReqstChannel.arg.f1);
        db.update(groupIdx | offset++, m_lpsSaWeighReqstChannel.arg.f2);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 20000 */
    if ( m_lpsSaWeighRespChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 2;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, m_lpsSaWeighRespChannel.command == LpsSaWeighReqstChannel::Command::ZERO ? m_lpsSaWeighRespChannel.success : false);
        db.update(groupIdx | offset++, m_lpsSaWeighRespChannel.command == LpsSaWeighReqstChannel::Command::RESET_BEST_BUCKET_WEIGHT ? m_lpsSaWeighRespChannel.success : false);
        db.update(groupIdx | offset++, m_lpsSaWeighRespChannel.command == LpsSaWeighReqstChannel::Command::WRITE_WEIGH_RANGE ? m_lpsSaWeighRespChannel.success : false);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 30000 */
    if (m_lpsSaWeighDebugChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 3;
        static constexpr uint32_t groupIdx = index << 16;

        /* LpsUpdtTbl_t m_weighUpdtTbl */
        db.update(groupIdx | 0x00, (int)m_lpsSaWeighDebugChannel.DebugLiftCylHePressStatus);
        db.update(groupIdx | 0x01, m_lpsSaWeighDebugChannel.DebugLiftCylHePress);
        db.update(groupIdx | 0x02, (int)m_lpsSaWeighDebugChannel.DebugLiftCylRePressStatus);
        db.update(groupIdx | 0x03, m_lpsSaWeighDebugChannel.DebugLiftCylRePress);
        db.update(groupIdx | 0x04, (int)m_lpsSaWeighDebugChannel.DebugLiftPositionStatus);
        db.update(groupIdx | 0x05, m_lpsSaWeighDebugChannel.DebugLiftCylNormLen);
        db.update(groupIdx | 0x06, (int)m_lpsSaWeighDebugChannel.DebugLiftPositionStatus);
        db.update(groupIdx | 0x07, m_lpsSaWeighDebugChannel.DebugLiftCylVel);
        db.update(groupIdx | 0x08, (int)m_lpsSaWeighDebugChannel.DebugHydOilTempStatus);
        db.update(groupIdx | 0x09, m_lpsSaWeighDebugChannel.DebugHydOilTemp);
        db.update(groupIdx | 0x0A, m_lpsSaWeighDebugChannel.DebugWeighUpdtClockKeyonSec);
        db.update(groupIdx | 0x0B, m_lpsSaWeighDebugChannel.DebugWeighUpdtPassCount);
        db.update(groupIdx | 0x0C, false /* ZeroButtonPress */);
        db.update(groupIdx | 0x0D, (int)m_lpsSaWeighDebugChannel.DebugTiltPositionStatus);
        db.update(groupIdx | 0x0E, m_lpsSaWeighDebugChannel.DebugTiltCylNormLen);
        db.update(groupIdx | 0x0F, (int)m_lpsSaWeighDebugChannel.DebugTiltPositionStatus);
        db.update(groupIdx | 0x10, m_lpsSaWeighDebugChannel.DebugTiltCylVel);
        db.update(groupIdx | 0x11, (int)m_lpsSaWeighDebugChannel.DebugBucketAngleStatus);
        db.update(groupIdx | 0x12, m_lpsSaWeighDebugChannel.DebugBucketAngle);
        db.update(groupIdx | 0x13, (int)m_lpsSaWeighDebugChannel.DebugRequestedGearStatus);
        db.update(groupIdx | 0x14, m_lpsSaWeighDebugChannel.DebugRequestedGear);
        db.update(groupIdx | 0x15, (bool)m_lpsSaWeighDebugChannel.m_LpsWrk.LiveWeighTbl.UseFastFilter);
        db.update(groupIdx | 0x16, m_lpsSaWeighDebugChannel.DebugWeighUpdtLoaderBktPayldTrgtWt);

        /* LpsWrkTbl_t m_LpsWrk */
        db.update(groupIdx | 0x17, m_lpsSaWeighDebugChannel.m_LpsWrk.LiftCylPressureV0);
        db.update(groupIdx | 0x18, m_lpsSaWeighDebugChannel.m_LpsWrk.InstWtLlwFilt);
        db.update(groupIdx | 0x19, m_lpsSaWeighDebugChannel.m_LpsWrk.InstWtDer);
        db.update(groupIdx | 0x1A, m_lpsSaWeighDebugChannel.m_LpsWrk.InstWtRaw.Val);
        db.update(groupIdx | 0x1B, (int)m_lpsSaWeighDebugChannel.m_LpsWrk.InstWtRaw.Stat);
        db.update(groupIdx | 0x1C, m_lpsSaWeighDebugChannel.m_LpsWrk.InstWtFilt);
        db.update(groupIdx | 0x1D, m_lpsSaWeighDebugChannel.m_LpsWrk.CylFlowConst.LiftHeFlowConst);
        db.update(groupIdx | 0x1E, m_lpsSaWeighDebugChannel.m_LpsWrk.CylFlowConst.LiftReToHeFlowRatio);
        db.update(groupIdx | 0x1F, (int)m_lpsSaWeighDebugChannel.m_LpsWrk.LinkageMovement.lift);
        db.update(groupIdx | 0x20, (int)m_lpsSaWeighDebugChannel.m_LpsWrk.LinkageMovement.tilt);
        db.update(groupIdx | 0x21, m_lpsSaWeighDebugChannel.m_LpsWrk.WrwTbl.OpTbl.Wt);
        db.update(groupIdx | 0x22, (int)m_lpsSaWeighDebugChannel.m_LpsWrk.WrwTbl.OpTbl.Warning);
        db.update(groupIdx | 0x23, (int)m_lpsSaWeighDebugChannel.m_LpsWrk.WrwTbl.OpTbl.Status);
        db.update(groupIdx | 0x24, (int)m_lpsSaWeighDebugChannel.m_LpsWrk.WrwTbl.OpTbl.Indicator);
        db.update(groupIdx | 0x25, (bool)m_lpsSaWeighDebugChannel.m_LpsWrk.WrwTbl.WkTbl.BeenBelowRange);
        db.update(groupIdx | 0x26, (int)m_lpsSaWeighDebugChannel.m_LpsWrk.LpsStallDetect.liftStalled);
        db.update(groupIdx | 0x27, (int)m_lpsSaWeighDebugChannel.m_LpsWrk.DumpStateStatus);
        db.update(groupIdx | 0x28, m_lpsSaWeighDebugChannel.m_LpsWrk.BestBktWt.Wt);
        db.update(groupIdx | 0x29, m_lpsSaWeighDebugChannel.m_LpsWrk.BestBktWt.PayloadCalcMeth);
        db.update(groupIdx | 0x2A, m_lpsSaWeighDebugChannel.m_LpsWrk.LowLiftWt.LastInput);
        db.update(groupIdx | 0x2B, m_lpsSaWeighDebugChannel.m_LpsWrk.LowLiftWt.MeanEst);
        db.update(groupIdx | 0x2C, m_lpsSaWeighDebugChannel.m_LpsWrk.LowLiftWt.MeanEstComp);
        db.update(groupIdx | 0x2D, m_lpsSaWeighDebugChannel.m_LpsWrk.LowLiftWt.VarianceEst);
        db.update(groupIdx | 0x2E, m_lpsSaWeighDebugChannel.m_LpsWrk.LowLiftWt.StdevEst);
        db.update(groupIdx | 0x2F, m_lpsSaWeighDebugChannel.m_LpsWrk.LowLiftWt.Confidence);
        db.update(groupIdx | 0x30, m_lpsSaWeighDebugChannel.m_LpsWrk.LowLiftWt.ConfidenceEst);
        db.update(groupIdx | 0x31, m_lpsSaWeighDebugChannel.m_LpsWrk.LowLiftWt.ConfidenceTimer);
        db.update(groupIdx | 0x32, m_lpsSaWeighDebugChannel.m_LpsWrk.LowLiftWt.Wt);
        db.update(groupIdx | 0x33, (int)m_lpsSaWeighDebugChannel.m_LpsWrk.LowLiftWt.Stat);
        db.update(groupIdx | 0x34, false /* ZeroAccepted */);
        db.update(groupIdx | 0x35, false /* TooHeavyToZero */);
        db.update(groupIdx | 0x36, (int)m_lpsSaWeighDebugChannel.m_LpsWrk.ZeroAdjTbl.ZeroAdjStatus);
        db.update(groupIdx | 0x37, m_lpsSaWeighDebugChannel.m_LpsWrk.DumpWtChangeData.DumpCumulativeWtChange);
        db.update(groupIdx | 0x38, (bool)m_lpsSaWeighDebugChannel.m_LpsWrk.DigDetectData.DigStarted);
        db.update(groupIdx | 0x39, (bool)m_lpsSaWeighDebugChannel.m_LpsWrk.DigDetectData.DigDetected);
        db.update(groupIdx | 0x3A, (int)m_lpsSaWeighDebugChannel.m_LpsWrk.DigDetectData.DigState);
        db.update(groupIdx | 0x3B, (bool)m_lpsSaWeighDebugChannel.m_LpsWrk.DigDetectData.WtStabilized);
        db.update(groupIdx | 0x3C, m_lpsSaWeighDebugChannel.m_LpsWrk.DigDetectData.DigDuration);
        db.update(groupIdx | 0x3D, m_lpsSaWeighDebugChannel.m_LpsWrk.LiveWeighTbl.Wt);
        db.update(groupIdx | 0x3E, (int)m_lpsSaWeighDebugChannel.m_LpsWrk.LiveWeighTbl.Stat);
        db.update(groupIdx | 0x3F, m_lpsSaWeighDebugChannel.reweighWarn);

        /* Lift Cylinder Head End Pressure */
        db.update(groupIdx | 0x40, m_lpsSaWeighDebugChannel.DebugLiftCylHePeriod);
        db.update(groupIdx | 0x41, m_lpsSaWeighDebugChannel.DebugLiftCylHeWidth);
        db.update(groupIdx | 0x42, m_lpsSaWeighDebugChannel.DebugLiftCylHeDc);
        db.update(groupIdx | 0x43, m_lpsSaWeighDebugChannel.DebugLiftCylHePress);

        /* Lift Cylinder Rod End Pressure */
        db.update(groupIdx | 0x44, m_lpsSaWeighDebugChannel.DebugLiftCylRePeriod);
        db.update(groupIdx | 0x45, m_lpsSaWeighDebugChannel.DebugLiftCylReWidth);
        db.update(groupIdx | 0x46, m_lpsSaWeighDebugChannel.DebugLiftCylReDc);
        db.update(groupIdx | 0x47, m_lpsSaWeighDebugChannel.DebugLiftCylRePress);

        /* Lift Cylinder */
        db.update(groupIdx | 0x48, m_lpsSaWeighDebugChannel.DebugLiftCylPeriod);
        db.update(groupIdx | 0x49, m_lpsSaWeighDebugChannel.DebugLiftCylWidth);
        db.update(groupIdx | 0x4A, m_lpsSaWeighDebugChannel.DebugLiftCylDc);
        db.update(groupIdx | 0x4B, m_lpsSaWeighDebugChannel.DebugLiftCylRawExt);
        db.update(groupIdx | 0x4C, m_lpsSaWeighDebugChannel.DebugLiftCylFiltExt);
        db.update(groupIdx | 0x4D, m_lpsSaWeighDebugChannel.DebugLiftCylNormLen);
        db.update(groupIdx | 0x4E, m_lpsSaWeighDebugChannel.DebugLiftCylVel);
        db.update(groupIdx | 0x4F, m_lpsSaWeighDebugChannel.DebugLiftAngle);

        /* Tilt Cylinder */
        db.update(groupIdx | 0x50, m_lpsSaWeighDebugChannel.DebugTiltCylPeriod);
        db.update(groupIdx | 0x51, m_lpsSaWeighDebugChannel.DebugTiltCylWidth);
        db.update(groupIdx | 0x52, m_lpsSaWeighDebugChannel.DebugTiltCylDc);
        db.update(groupIdx | 0x53, m_lpsSaWeighDebugChannel.DebugTiltCylRawLen);
        db.update(groupIdx | 0x54, m_lpsSaWeighDebugChannel.DebugTiltCylVel);
        db.update(groupIdx | 0x55, m_lpsSaWeighDebugChannel.DebugTiltAngle);
        db.update(groupIdx | 0x56, m_lpsSaWeighDebugChannel.DebugTiltAngleABC);

        /* Overloads */
        db.update(groupIdx | 0x57, m_lpsSaWeighDebugChannel.m_LpsWrk.OverloadWarnTbl.BucketLoadFactor);
        db.update(groupIdx | 0x58, (bool)m_lpsSaWeighDebugChannel.m_LpsWrk.OverloadWarnTbl.DigReverseFlag);
        db.update(groupIdx | 0x59, (bool)m_lpsSaWeighDebugChannel.m_LpsWrk.OverloadWarnTbl.InOverloadRange);
        db.update(groupIdx | 0x5A, false /* Previously InWaitForLatch */);
        db.update(groupIdx | 0x5B, m_lpsSaWeighDebugChannel.m_LpsWrk.OverloadWarnTbl.Level != LPS_WEIGH_OVERLOAD_LEVEL_NONE);
        db.update(groupIdx | 0x5C, m_lpsSaWeighDebugChannel.m_LpsWrk.OverloadWarnTbl.PrevDigState);

        /* tipoff assists channels */
        db.update(groupIdx | 0x5D, (bool)m_lpsSaWeighDebugChannel.m_LpsWrk.BestBktWt.TipoffLiveWeightInUse);
        db.update(groupIdx | 0x5E, 0); /* not used */
        db.update(groupIdx | 0x5F, m_lpsSaWeighDebugChannel.m_TipoffInputs.bucket_current_weight);
        db.update(groupIdx | 0x60, m_lpsSaWeighDebugChannel.m_TipoffInputs.bucket_current_weight_accuracy);
        db.update(groupIdx | 0x61, m_lpsSaWeighDebugChannel.m_TipoffInputs.eef_imu_accelX);
        db.update(groupIdx | 0x62, m_lpsSaWeighDebugChannel.m_TipoffInputs.eef_imu_accelY);
        db.update(groupIdx | 0x63, m_lpsSaWeighDebugChannel.m_TipoffInputs.eef_imu_accelZ);
        db.update(groupIdx | 0x64, m_lpsSaWeighDebugChannel.m_TipoffInputs.input_status.data);
        db.update(groupIdx | 0x65, (bool)m_lpsSaWeighDebugChannel.m_TipoffInputs.invalidate_outputs);
        db.update(groupIdx | 0x66, m_lpsSaWeighDebugChannel.m_TipoffInputs.lift_angle);
        db.update(groupIdx | 0x67, m_lpsSaWeighDebugChannel.m_TipoffInputs.lift_he_pressure);
        db.update(groupIdx | 0x68, m_lpsSaWeighDebugChannel.m_TipoffInputs.lift_re_pressure);
        db.update(groupIdx | 0x69, m_lpsSaWeighDebugChannel.m_TipoffInputs.lift_valve_cmd);
        db.update(groupIdx | 0x6A, m_lpsSaWeighDebugChannel.m_TipoffInputs.steering_angle);
        db.update(groupIdx | 0x6B, m_lpsSaWeighDebugChannel.m_TipoffInputs.tilt_extension);
        db.update(groupIdx | 0x6C, m_lpsSaWeighDebugChannel.m_TipoffInputs.tilt_he_pressure);
        db.update(groupIdx | 0x6D, m_lpsSaWeighDebugChannel.m_TipoffInputs.tilt_re_pressure);
        db.update(groupIdx | 0x6E, m_lpsSaWeighDebugChannel.m_TipoffInputs.tilt_valve_cmd);
        db.update(groupIdx | 0x6F, m_lpsSaWeighDebugChannel.m_TipoffInputs.tipoff_mode);
        db.update(groupIdx | 0x70, m_lpsSaWeighDebugChannel.m_TipoffInputs.tool_mass);
        db.update(groupIdx | 0x71, m_lpsSaWeighDebugChannel.m_TipoffInputs.truck_start_weight);
        db.update(groupIdx | 0x72, m_lpsSaWeighDebugChannel.m_TipoffInputs.truck_target_wt);
        db.update(groupIdx | 0x73, m_lpsSaWeighDebugChannel.m_TipoffOutputs.arbitrated_payload_norm_error_out);
        db.update(groupIdx | 0x74, m_lpsSaWeighDebugChannel.m_TipoffOutputs.current_weight_norm_error_out);
        db.update(groupIdx | 0x75, m_lpsSaWeighDebugChannel.m_TipoffOutputs.error_code_out);
        db.update(groupIdx | 0x76, m_lpsSaWeighDebugChannel.m_TipoffOutputs.payload_norm_stdev_out);
        db.update(groupIdx | 0x77, m_lpsSaWeighDebugChannel.m_TipoffOutputs.payload_send_to_CPM);
        db.update(groupIdx | 0x78, m_lpsSaWeighDebugChannel.m_TipoffOutputs.payload_status_send_to_CPM);
        db.update(groupIdx | 0x79, m_lpsSaWeighDebugChannel.m_TipoffOutputs.pcs_weight_accuracy_out);
        db.update(groupIdx | 0x7A, m_lpsSaWeighDebugChannel.m_TipoffOutputs.spill_rate_out);
        db.update(groupIdx | 0x7B, m_lpsSaWeighDebugChannel.m_TipoffOutputs.tilt_pressure_out);
        db.update(groupIdx | 0x7C, m_lpsSaWeighDebugChannel.m_TipoffOutputs.tilt_sensitivity_out);
        db.update(groupIdx | 0x7D, m_lpsSaWeighDebugChannel.m_TipoffOutputs.weigh_status_out);
        db.update(groupIdx | 0x7E, m_lpsSaWeighDebugChannel.m_TipoffInputs.zero_offset);
        db.update(groupIdx | 0x7F, m_lpsSaWeighDebugChannel.m_TipoffInputs.simple_cal_factor);
        db.update(groupIdx | 0x80, m_lpsSaWeighDebugChannel.m_TipoffInputs.bucket_angle);
        db.update(groupIdx | 0x81, (bool)m_lpsSaWeighDebugChannel.m_TipoffInputs.unlatch_trigger);

        /* Tilt Cylinder Head End Pressure */
        db.update(groupIdx | 0x82, m_lpsSaWeighDebugChannel.DebugTiltCylHePeriod);
        db.update(groupIdx | 0x83, m_lpsSaWeighDebugChannel.DebugTiltCylHeWidth);
        db.update(groupIdx | 0x84, m_lpsSaWeighDebugChannel.DebugTiltCylHeDc);
        db.update(groupIdx | 0x85, m_lpsSaWeighDebugChannel.DebugTiltCylHePress);

        /* Tilt Cylinder Rod End Pressure */
        db.update(groupIdx | 0x86, m_lpsSaWeighDebugChannel.DebugTiltCylRePeriod);
        db.update(groupIdx | 0x87, m_lpsSaWeighDebugChannel.DebugTiltCylReWidth);
        db.update(groupIdx | 0x88, m_lpsSaWeighDebugChannel.DebugTiltCylReDc);
        db.update(groupIdx | 0x89, m_lpsSaWeighDebugChannel.DebugTiltCylRePress);

        /* more tip-assist channels */
        db.update(groupIdx | 0x8A, m_lpsSaWeighDebugChannel.m_TipoffInputs.anchor_zero_offset);
        db.update(groupIdx | 0x8B, m_lpsSaWeighDebugChannel.m_TipoffInputs.anchor_factor);
        db.update(groupIdx | 0x8C, m_lpsSaWeighDebugChannel.m_TipoffOutputs.bucket_payload_target);
        db.update(groupIdx | 0x8D, m_lpsSaWeighDebugChannel.m_TipoffInputs.pass_count);
        db.update(groupIdx | 0x8E, m_lpsSaWeighDebugChannel.m_TipoffInputs.lift_norm_angle);
        db.update(groupIdx | 0x8F, m_lpsSaWeighDebugChannel.m_TipoffInputs.lift_norm_length);
        db.update(groupIdx | 0x90, m_lpsSaWeighDebugChannel.m_TipoffInputs.tilt_norm_angle);
        db.update(groupIdx | 0x91, m_lpsSaWeighDebugChannel.m_TipoffInputs.tilt_norm_length);
        db.update(groupIdx | 0x92, m_lpsSaWeighDebugChannel.m_TipoffOutputs.min_secure_bucket_angle);
        db.update(groupIdx | 0x93, m_lpsSaWeighDebugChannel.m_TipoffOutputs.unsecured_PFW_status);
        db.update(groupIdx | 0x94, m_lpsSaWeighDebugChannel.m_TipoffOutputs.unsecured_payload_lower_bound_norm);
        db.update(groupIdx | 0x95, m_lpsSaWeighDebugChannel.m_TipoffOutputs.unsecured_payload_upper_bound_norm);
        db.update(groupIdx | 0x96, m_lpsSaWeighDebugChannel.m_TipoffInputs.friction_mu);
        db.update(groupIdx | 0x97, m_lpsSaWeighDebugChannel.m_TipoffInputs.friction_offset);

        // Chassis IMU
        db.update(groupIdx | 0x98, m_lpsSaWeighDebugChannel.chassisImuGravityX);
        db.update(groupIdx | 0x99, m_lpsSaWeighDebugChannel.chassisImuGravityY);
        db.update(groupIdx | 0x9A, m_lpsSaWeighDebugChannel.chassisImuGravityZ);
        db.update(groupIdx | 0x9B, m_lpsSaWeighDebugChannel.chassisImuVelocityX);
        db.update(groupIdx | 0x9C, m_lpsSaWeighDebugChannel.chassisImuVelocityY);
        db.update(groupIdx | 0x9D, m_lpsSaWeighDebugChannel.chassisImuVelocityZ);
        db.update(groupIdx | 0x9E, m_lpsSaWeighDebugChannel.chassisImuBiasAngVelX);
        db.update(groupIdx | 0x9F, m_lpsSaWeighDebugChannel.chassisImuBiasAngVelY);
        db.update(groupIdx | 0xA0, m_lpsSaWeighDebugChannel.chassisImuBiasAngVelZ);
        db.update(groupIdx | 0xA1, m_lpsSaWeighDebugChannel.chassisImuPitch);
        db.update(groupIdx | 0xA2, m_lpsSaWeighDebugChannel.chassisImuRoll);
        db.update(groupIdx | 0xA3, m_lpsSaWeighDebugChannel.chassisImuSensorLinAccStatus);
        db.update(groupIdx | 0xA4, m_lpsSaWeighDebugChannel.chassisImuSensorAngVelStatus);
        db.update(groupIdx | 0xA5, m_lpsSaWeighDebugChannel.chassisImuBiasMagJerk);
        db.update(groupIdx | 0xA6, m_lpsSaWeighDebugChannel.chassisImuBiasMagAngAccel);
        db.update(groupIdx | 0xA7, m_lpsSaWeighDebugChannel.chassisImuBiasMaxAngVel);
        db.update(groupIdx | 0xA8, m_lpsSaWeighDebugChannel.chassisImuLinAccX);
        db.update(groupIdx | 0xA9, m_lpsSaWeighDebugChannel.chassisImuLinAccY);
        db.update(groupIdx | 0xAA, m_lpsSaWeighDebugChannel.chassisImuLinAccZ);
        db.update(groupIdx | 0xAB, m_lpsSaWeighDebugChannel.chassisImuAngVelX);
        db.update(groupIdx | 0xAC, m_lpsSaWeighDebugChannel.chassisImuAngVelY);
        db.update(groupIdx | 0xAD, m_lpsSaWeighDebugChannel.chassisImuAngVelZ);

        // Added for Acceleration Compensation
        db.update(groupIdx | 0xB0, m_lpsSaWeighDebugChannel.DebugLiftAngVel);
        db.update(groupIdx | 0xB1, m_lpsSaWeighDebugChannel.m_LpsWrk.LiftPositionFilt.velocity);
        db.update(groupIdx | 0xB2, m_lpsSaWeighDebugChannel.m_LpsWrk.WrwTbl.WkTbl.result.weightAveRaw);
        db.update(groupIdx | 0xB3, m_lpsSaWeighDebugChannel.m_LpsWrk.WrwTbl.WkTbl.result.weightAve);
        db.update(groupIdx | 0xB4, m_lpsSaWeighDebugChannel.m_LpsWrk.LiftPositionFilt.length);
        db.update(groupIdx | 0xB5, m_lpsSaWeighDebugChannel.m_LpsWrk.LiftCylPressure);
        db.update(groupIdx | 0xB6, m_lpsSaWeighDebugChannel.m_LpsWrk.InstWtRawPreTiltComp);
        db.update(groupIdx | 0xB7, m_lpsSaWeighDebugChannel.m_LpsWrk.InstWtRawPostTiltComp);
        db.update(groupIdx | 0xB8, m_lpsSaWeighDebugChannel.m_LpsWrk.LiftPositionFilt.angle);

        // Added for Pitch and Roll Compensation
        db.update(groupIdx | 0xC0, m_lpsSaWeighDebugChannel.m_LpsWrk.WrwTbl.WkTbl.result.weightAveRawIMUComp);
        db.update(groupIdx | 0xC1, m_lpsSaWeighDebugChannel.m_LpsWrk.LiftCylPressureIMUAdjusted);

        db.update(groupIdx | 0xFF, updateCounter++);
    }

    /* index group: 40000 */
    if ( m_lpsSaWeighInitDebugChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 4;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, 1); /* unused */
        db.update(groupIdx | offset++, (int)m_lpsSaWeighInitDebugChannel.m_WeighInitTbl.MachSpecificCfg.CalibTbl.CalStatus);
        db.update(groupIdx | offset++, m_lpsSaWeighInitDebugChannel.m_WeighInitTbl.MachSpecificCfg.CalibTbl.CalWeight);
        db.update(groupIdx | offset++, m_lpsSaWeighInitDebugChannel.m_WeighInitTbl.MachSpecificCfg.CalibTbl.CalAdjust);
        db.update(groupIdx | offset++, m_lpsSaWeighInitDebugChannel.m_WeighInitTbl.MachSpecificCfg.CalibTbl.ZeroWeight);
        db.update(groupIdx | offset++, m_lpsSaWeighInitDebugChannel.m_WeighInitTbl.MachSpecificCfg.StartOfWeigh);
        db.update(groupIdx | offset++, m_lpsSaWeighInitDebugChannel.m_WeighInitTbl.MachSpecificCfg.TiltComp.TiltCompGainScalar);
        db.update(groupIdx | offset++, m_lpsSaWeighInitDebugChannel.m_WeighInitTbl.MachSpecificCfg.DigConfig.DigTargetWt);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 50000 */
    if ( m_lpsSaWeighTxChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 5;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, (int)m_lpsSaWeighTxChannel.DigStat);
        db.update(groupIdx | offset++, (int)m_lpsSaWeighTxChannel.CalStat);
        db.update(groupIdx | offset++, (int)m_lpsSaWeighTxChannel.DumpStat);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.BestBktWtInTonnes);
        db.update(groupIdx | offset++, (int)0); // This was zero status, but never worked
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.PayloadCalcMeth);
        db.update(groupIdx | offset++, (int)m_lpsSaWeighTxChannel.LiftCylVel.Stat);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.LiftCylVel.Val);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.WeighRange.WeighRangeBottom);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.WeighRange.WeighRangeSize);
        db.update(groupIdx | offset++, (int)m_lpsSaWeighTxChannel.LiftPosition.status);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.LiftPosition.percentCylinderLength);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.CAN11MessageTimeoutFlag);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.SimpleCalAdjust);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.ZeroWeight);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.WarmupLiftsRequired);
        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 60000 */
    if ( m_lpsSaJobMgrTxChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 6;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, m_lpsSaJobMgrTxChannel.passCount);
        db.update(groupIdx | offset++, m_lpsSaJobMgrTxChannel.truckTargetWeight);
        db.update(groupIdx | offset++, (float)m_lpsSaJobMgrTxChannel.truckWeight);
        db.update(groupIdx | offset++, m_lpsSaJobMgrTxChannel.materialId);
        db.update(groupIdx | offset++, (int)m_lpsSaJobMgrTxChannel.ManualTipOffState);
        db.update(groupIdx | offset++, (int)m_lpsSaJobMgrTxChannel.TipOffTriggerType);
        db.update(groupIdx | offset++, (int)m_lpsSaJobMgrTxChannel.TipOffState);
        db.update(groupIdx | offset++, (int)m_lpsSaJobMgrTxChannel.OperationMode);
        db.update(groupIdx | offset++, (int)m_lpsSaJobMgrTxChannel.StandbyState);
        db.update(groupIdx | offset++, (int)m_lpsSaJobMgrTxChannel.ClearMinusOneEnableStat);
        db.update(groupIdx | offset++, m_lpsSaJobMgrTxChannel.DispBestBktWt.val);
        db.update(groupIdx | offset++, (int)m_lpsSaJobMgrTxChannel.DispBestBktWt.isOk);
        db.update(groupIdx | offset++, (int)m_lpsSaJobMgrTxChannel.TipOffStateCfg);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 70000 */
    if ( m_pwmInputChannels.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 7;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, (int)m_pwmInputChannels.PwmData.ActualTimeUs);
        db.update(groupIdx | offset++, m_pwmInputChannels.PwmData.ExecTime);
        db.update(groupIdx | offset++, m_pwmInputChannels.PwmData.DiffTime);
        db.update(groupIdx | offset++, m_pwmInputChannels.PwmData.Exp);

        db.update(groupIdx | offset++, m_pwmInputChannels.PwmData.Width[0]);
        db.update(groupIdx | offset++, m_pwmInputChannels.PwmData.Width[1]);
        db.update(groupIdx | offset++, m_pwmInputChannels.PwmData.Width[2]);
        db.update(groupIdx | offset++, m_pwmInputChannels.PwmData.Width[3]);
        db.update(groupIdx | offset++, m_pwmInputChannels.PwmData.Period[0]);
        db.update(groupIdx | offset++, m_pwmInputChannels.PwmData.Period[1]);
        db.update(groupIdx | offset++, m_pwmInputChannels.PwmData.Period[2]);
        db.update(groupIdx | offset++, m_pwmInputChannels.PwmData.Period[3]);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 0x8xxxx - Cycle Segmentation */
    if ( m_cycleSegTxData.update() || !init_done ) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 8;
        static constexpr uint32_t groupIdx = index << 16;

        db.update(groupIdx | 0, m_cycleSegTxData.activeSegmentId);
        db.update(groupIdx | 1, m_cycleSegTxData.digState);
        db.update(groupIdx | 2, m_cycleSegTxData.segmentLastCompletedId);
        db.update(groupIdx | 3, m_cycleSegTxData.segmentSecondsSinceLastEnd);
        db.update(groupIdx | 4, m_cycleSegTxData.segmentSequenceNumber);

        db.update(groupIdx | 5, m_cycleSegTxData.cycleSegIn.ground_spd_kph);
        db.update(groupIdx | 6, m_cycleSegTxData.cycleSegIn.payload_ratio);
        db.update(groupIdx | 7, m_cycleSegTxData.cycleSegIn.payload_ratio_status);
        db.update(groupIdx | 8, m_cycleSegTxData.cycleSegIn.payload_ratio_raw);
        db.update(groupIdx | 9, m_cycleSegTxData.cycleSegIn.payload_ratio_raw_status);
        db.update(groupIdx | 10, m_cycleSegTxData.cycleSegIn.lift_valve_cmd);
        db.update(groupIdx | 11, m_cycleSegTxData.cycleSegIn.tilt_valve_cmd);
        db.update(groupIdx | 12, m_cycleSegTxData.cycleSegIn.bucket_angle);
        db.update(groupIdx | 13, m_cycleSegTxData.cycleSegIn.lift_angle);
        db.update(groupIdx | 14, m_cycleSegTxData.cycleSegIn.desired_gear);
        db.update(groupIdx | 15, m_cycleSegTxData.cycleSegIn.engine_spd_rpm);
        db.update(groupIdx | 16, m_cycleSegTxData.cycleSegIn.tilt_lever_cmd);
        db.update(groupIdx | 17, m_cycleSegTxData.cycleSegIn.tilt_cyl_pos);
        db.update(groupIdx | 18, m_cycleSegTxData.cycleSegIn.machine_idle_status);
        db.update(groupIdx | 19, m_cycleSegTxData.cycleSegIn.keyswitch_state);
        db.update(groupIdx | 20, m_cycleSegTxData.cycleSegIn.real_time);
        db.update(groupIdx | 21, m_cycleSegTxData.cycleSegIn.realTime_status);
        db.update(groupIdx | 22, m_cycleSegTxData.cycleSegIn.timezone_offset);
        db.update(groupIdx | 23, m_cycleSegTxData.cycleSegIn.total_fuel_high_res);
        db.update(groupIdx | 24, m_cycleSegTxData.cycleSegIn.total_fuel_low_res);
        db.update(groupIdx | 25, m_cycleSegTxData.cycleSegIn.fuel_rate);
        db.update(groupIdx | 26, m_cycleSegTxData.cycleSegIn.ARD_fuel_rate);
        db.update(groupIdx | 27, m_cycleSegTxData.cycleSegIn.GPS_latitude);
        db.update(groupIdx | 28, m_cycleSegTxData.cycleSegIn.GPS_longitude);
        db.update(groupIdx | 29, m_cycleSegTxData.cycleSegIn.GPS_status);
        db.update(groupIdx | 30, m_cycleSegTxData.cycleSegIn.service_hour_meter);
        db.update(groupIdx | 31, m_cycleSegTxData.cycleSegIn.payload_weight);
        db.update(groupIdx | 32, m_cycleSegTxData.cycleSegIn.payload_weight_status);
        db.update(groupIdx | 33, m_cycleSegTxData.cycleSegIn.payload_calc_method);
        db.update(groupIdx | 34, m_cycleSegTxData.cycleSegIn.extForceNormalized);
        db.update(groupIdx | 35, m_cycleSegTxData.cycleSegIn.impl_operation_status);
        db.update(groupIdx | 36, m_cycleSegTxData.cycleSegIn.Engine_Load_Factor);

        db.update(groupIdx | 37, m_cycleSegTxData.cycleSegOut.commit_segment_record);
        db.update(groupIdx | 38, m_cycleSegTxData.cycleSegOut.segment_record_id);
        db.update(groupIdx | 39, m_cycleSegTxData.cycleSegOut.segment_rec_start_simTime);
        db.update(groupIdx | 40, m_cycleSegTxData.cycleSegOut.segment_rec_duration);
        db.update(groupIdx | 41, m_cycleSegTxData.cycleSegOut.segment_rec_distance);
        db.update(groupIdx | 42, m_cycleSegTxData.cycleSegOut.segment_rec_start_real_time);
        db.update(groupIdx | 43, m_cycleSegTxData.cycleSegOut.segment_rec_fuel_used);
        db.update(groupIdx | 44, m_cycleSegTxData.cycleSegOut.segment_rec_latitude);
        db.update(groupIdx | 45, m_cycleSegTxData.cycleSegOut.segment_rec_longitude);
        db.update(groupIdx | 46, m_cycleSegTxData.cycleSegOut.segment_rec_idle_time);
        db.update(groupIdx | 47, m_cycleSegTxData.cycleSegOut.segment_rec_hour_meter);
        db.update(groupIdx | 48, m_cycleSegTxData.cycleSegOut.segment_rec_payload);
        db.update(groupIdx | 49, m_cycleSegTxData.cycleSegOut.segment_rec_payload_calc_method);
        db.update(groupIdx | 50, m_cycleSegTxData.cycleSegOut.commit_rec_gps);
        db.update(groupIdx | 51, m_cycleSegTxData.cycleSegOut.segment_dig_state);
        db.update(groupIdx | 52, m_cycleSegTxData.cycleSegOut.segment_last_completed_id);
        db.update(groupIdx | 53, m_cycleSegTxData.cycleSegOut.segment_time_since_last_end);
        db.update(groupIdx | 54, m_cycleSegTxData.cycleSegOut.segment_sequence_number);
        db.update(groupIdx | 55, m_cycleSegTxData.cycleSegOut.keyswitch_override_flag);
        db.update(groupIdx | 56, m_cycleSegTxData.cycleSegOut.segment_active_segment_id);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 90000 */
    if ( m_lpsSaJobMgrReqstChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 9;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command == LpsSaJobMgrReqstChannel::Command::ZERO);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command == LpsSaJobMgrReqstChannel::Command::MINUS_ONE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command == LpsSaJobMgrReqstChannel::Command::CLEAR);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command == LpsSaJobMgrReqstChannel::Command::STORE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command == LpsSaJobMgrReqstChannel::Command::STANDBY_ACTIVATE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command == LpsSaJobMgrReqstChannel::Command::STANDBY_DEACTIVATE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command == LpsSaJobMgrReqstChannel::Command::TIPOFF_MODE_TOGGLE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command == LpsSaJobMgrReqstChannel::Command::MANUAL_TIPOFF_ACTIVATE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command == LpsSaJobMgrReqstChannel::Command::MANUAL_TIPOFF_DEACTIVATE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command == LpsSaJobMgrReqstChannel::Command::WRITE_TIPOFF_TRIGGER_TYPE);
        db.update(groupIdx | offset++, (int)m_lpsSaJobMgrReqstChannel.data.tipoffTriggerType);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command == LpsSaJobMgrReqstChannel::Command::WRITE_TIPOFF_MODE);
        db.update(groupIdx | offset++, (int)m_lpsSaJobMgrReqstChannel.data.tipoffMode);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command == LpsSaJobMgrReqstChannel::Command::REWEIGH);

        { // Target truck weight command?
            bool found = false;
            for (const auto& r : m_lpsSaJobMgrReqstChannel.requests) {
                if (LpsSaJobMgrReqstCommand::WRITE_TRUCK_TARGET_WEIGHT == r.command) {
                    db.update(groupIdx | offset++, true);
                    db.update(groupIdx | offset++, r.truckTargetWeight());
                    found = true;
                    break;
                }
            }
            if (!found) {
                // No target truck weight command.
                db.update(groupIdx | offset++, false);
                db.update(groupIdx | offset++, 0.f);
            }
        }

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: A0000 */
    if ( m_lpsSaJobMgrRespChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 10;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        /*
         * These were never working anyway so they are now just set to 0
         */
//        db.update(groupIdx | offset++, 0 /* ZeroResp */);
//        db.update(groupIdx | offset++, 0 /* MinusOneResp */);
//        db.update(groupIdx | offset++, 0 /* ClearResp */);
//        db.update(groupIdx | offset++, 0 /* StoreResp */);
//        db.update(groupIdx | offset++, 0 /* StandByActResp */);
//        db.update(groupIdx | offset++, 0 /* StandByDeActResp */);
//        db.update(groupIdx | offset++, 0 /* TipOffTruckPileToggleResp */);
//        db.update(groupIdx | offset++, 0 /* TipOffActResp */);
//        db.update(groupIdx | offset++, 0 /* TipOffDeactResp */);
//        db.update(groupIdx | offset++, 0 /* ReWeighResp */);
//        db.update(groupIdx | offset++, 0 /* TargetWeightResp */);
//        db.update(groupIdx | offset++, 0 /* TipOffTriggerTypeResp */);
//        db.update(groupIdx | offset++, 0 /* TipOffStateResp */);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: B0000 */
    if (m_lpsSaJobMgrDebugChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 11;
        static constexpr uint32_t groupIdx = index << 16;

        db.update(groupIdx | 0x00, m_lpsSaJobMgrDebugChannel.currentState);
        db.update(groupIdx | 0x01, m_lpsSaJobMgrDebugChannel.tipoffAssistActivationCount);

        db.update(groupIdx | 0xFF, updateCounter++);
    }

    /* index group: C0000 */
    if ( m_switchInputScs.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 12;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        // read store button press
        db.update(groupIdx | offset++, m_switchInputScs.get_STG_value(3));

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: D0000 */
    if ( m_lpsSaNvmDataChannel.update() || !init_done)
    {
       static int updateCounter = 0;
       static constexpr uint32_t index = 13;
       static constexpr uint32_t groupIdx = index << 16;
       int offset = 0;

       // The expression below expands into a for-loop to DB_PUSH: raise_slow_empty_lift_heights[0], raise_slow_empty_lift_heights[1], ... , raise_slow_empty_lift_heights[10]
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_slow_empty_lift_heights, 11)

       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_slow_empty_pressures, 11)
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.lower_slow_empty_lift_heights, 11)
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.lower_slow_empty_pressures, 11)
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_slow_full_lift_heights, 11)
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_slow_full_pressures, 11)
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.lower_slow_full_lift_heights, 11)
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.lower_slow_full_pressures, 11)
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_speed_empty_slow);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_speed_empty_fast);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_fast_delta_p_empty);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_speed_full_slow);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_speed_full_fast);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_fast_delta_p_full);

       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.lift_full_lower_DC_inf_value);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.lift_full_raise_DC_inf_value);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.tilt_full_dump_DC_inf_value);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.tilt_full_rack_DC_inf_value);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.pcs_vel_slope);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.pcs_cal_weight);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.zero_weight);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.cal_adjust);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.temp_slope);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.empty_temp);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.full_temp);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.empty_bucket_weight_est);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.cal_adjust_temp);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.hyd_oil_type_index);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.tilt_dump_stop_angle_inf_value);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.tilt_rack_stop_angle_inf_value);

       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.FullSlowImuOffsetFinal));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.FullSlowImuOffsetTemp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.FullSlowImuOffsetTemp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.FullSlowImuOffsetTemp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.EmptySlowImuOffsetTemp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.EmptySlowImuOffsetTemp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.EmptySlowImuOffsetTemp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.FullSlowLumpedWeightTemp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.FullSlowLumpedWeightTemp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.FullSlowLumpedWeightTemp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.EmptySlowLumpedWeightTemp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.EmptySlowLumpedWeightTemp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.EmptySlowLumpedWeightTemp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.EmptySlowImuOffsetFinal));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.FullSlowLumpedWeightFinal));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.EmptySlowLumpedWeightFinal));

       db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: E0000 */
    if ( m_lpsSaNvmOnTheFlyDataChannel.update() || !init_done)
    {
       static int updateCounter = 0;
       static constexpr uint32_t index = 14;
       static constexpr uint32_t groupIdx = index << 16;
       int offset = 0;

       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.statusFlags.CalInProgress));
       DB_PUSH(static_cast<uint32_t>(0)); // Placeholder for removed channel.
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.statusFlags.EmptyBktCalDone));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.statusFlags.FullBktCalDone));

       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.HydOilTempMet));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.EnforceRaiseDetent));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.EnforceLowerDetent));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.RaiseFastVelDone));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.RaiseSlowFitDone));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.RaiseFastFitDone));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.LowerSlowFitDone));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.InternalStep));

       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calUpdates.LiftHePres_Stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calUpdates.LiftRePres_Stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calUpdates.LiftCylLengthNorm_Stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calUpdates.HydOilTemp_Stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calUpdates.LiftCylVel_Stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calUpdates.TiltCylLengthNorm_Stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calUpdates.BktAngle_Stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calUpdates.LiftLeverInfo_LeverInfoAvailable));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calUpdates.LiftLeverInfo_Faulted));

       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.RaiseNumPoints);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.LowerNumPoints);

       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.FullSlowImuOffsetFinal));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.FullSlowImuOffsetTemp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.FullSlowImuOffsetTemp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.FullSlowImuOffsetTemp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.EmptySlowImuOffsetTemp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.EmptySlowImuOffsetTemp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.EmptySlowImuOffsetTemp3));

       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.LpsCalOvrState);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.LiftBottomFlag);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.LiftTopFlag);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.LpsCalAppInfCalOvrActive);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.LpsCalAppInfLowerCmdLmt);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.LpsCalAppInfRaiseCmdLmt);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.LiftFaulted);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.LiftInCenter);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.LiftInLowerDetent);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.LiftInRaiseDetent);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.LiftValveCmdPercent);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.CalOvrAcknowledge);

       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.FullSlowLumpedWeightTemp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.FullSlowLumpedWeightTemp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.FullSlowLumpedWeightTemp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.EmptySlowLumpedWeightTemp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.EmptySlowLumpedWeightTemp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.EmptySlowLumpedWeightTemp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.EmptySlowImuOffsetFinal));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.FullSlowLumpedWeightFinal));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curveInfo.IMUCalResults.EmptySlowLumpedWeightFinal));

       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.TiltOverrides.CalTiltOverrideComplete);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.TiltOverrides.CalTiltOverrideFail);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.TiltOverrides.CountOfSamples);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.TiltOverrides.DesiredTiltExtmm);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.TiltOverrides.LpsCalTiltOvrStartRequest);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.TiltOverrides.LpsCalTiltOvrState);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.TiltOverrides.TiltDumpCmdOvr);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.TiltOverrides.TiltNoiseMax);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.calOverrides.TiltOverrides.TiltNoiseMin);
       
       db.update(groupIdx | 255, updateCounter++);

    }

    /* index group: Fxxxx - Work Order Assist */
    if ( m_workOrderAssistTxChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 15;
        static constexpr uint32_t groupIdx = index << 16;

        db.update(groupIdx | 0, m_workOrderAssistTxChannel.activityDetected);
        db.update(groupIdx | 1, m_workOrderAssistTxChannel.activeSiteId);
        db.update(groupIdx | 2, static_cast<int32_t>(m_workOrderAssistTxChannel.activeJobId)); // Narrowing Conversion
        db.update(groupIdx | 3, m_workOrderAssistTxChannel.hubServiceTxErrorCount);
        db.update(groupIdx | 4, m_workOrderAssistTxChannel.hubServiceTxSuccessCount);
        db.update(groupIdx | 5, m_workOrderAssistTxChannel.hubServiceRxCount);
        db.update(groupIdx | 6, m_workOrderAssistTxChannel.hubServiceCommsActive);
        db.update(groupIdx | 7, m_workOrderAssistTxChannel.numberOfJobs);
        // ...
        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 100000 - Widgets Debug Data */
    if ( m_widgetsDebugdata.update() | !init_done ) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 16;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, m_widgetsDebugdata.getDistance().ForwardMm);
        db.update(groupIdx | offset++, m_widgetsDebugdata.getDistance().ReverseMm);
        db.update(groupIdx | offset++, (bool)m_widgetsDebugdata.getDistance().Status);
        db.update(groupIdx | offset++, m_widgetsDebugdata.getRotation().Forward);
        db.update(groupIdx | offset++, m_widgetsDebugdata.getRotation().Reverse);
        db.update(groupIdx | offset++, (bool)m_widgetsDebugdata.getRotation().Status);
        db.update(groupIdx | offset++, m_widgetsDebugdata.getDigTimeCurrent());
        db.update(groupIdx | offset++, m_widgetsDebugdata.getTravelingLoadedRevs());
        db.update(groupIdx | offset++, (int)m_widgetsDebugdata.getDigState());
        db.update(groupIdx | offset++, m_widgetsDebugdata.getGroundSpeedInfo().speed);
        db.update(groupIdx | offset++, m_widgetsDebugdata.getGroundSpeedInfo().data_status);
        db.update(groupIdx | offset++, m_widgetsDebugdata.getGearInfo().gear);
        db.update(groupIdx | offset++, (int)m_widgetsDebugdata.getGearInfo().gear_status);
        // ...
        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 11xxxx - Display State */
    if ( m_displayStateChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 17;
        static constexpr uint32_t groupIdx = index << 16;

        db.update(groupIdx | 0, m_displayStateChannel.state.getHeartbeatCount());
        db.update(groupIdx | 1, m_displayStateChannel.state.isServiceModeEnableCodeEntered());
        db.update(groupIdx | 2, m_displayStateChannel.state.isInServiceMode());
        db.update(groupIdx | 3, m_displayStateChannel.state.getDocumentId());
        // ...
        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 12xxxx - Tip-Off Assist */
    if ( m_tipoffModelTestPoints.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 18;
        static constexpr uint32_t groupIdx = index << 16;

        db.update(groupIdx | 0x00, m_tipoffModelTestPoints.toa_sfuncOutRawMassTonne);
        db.update(groupIdx | 0x01, m_tipoffModelTestPoints.toa_payloadAdjusted);
        db.update(groupIdx | 0x02, m_tipoffModelTestPoints.toa_sfuncInTiltForce);
        db.update(groupIdx | 0x03, m_tipoffModelTestPoints.toa_sfuncInLiftForce);
        db.update(groupIdx | 0x04, m_tipoffModelTestPoints.toa_sfuncInGravX);
        db.update(groupIdx | 0x05, m_tipoffModelTestPoints.toa_sfuncInGravY);
        db.update(groupIdx | 0x06, m_tipoffModelTestPoints.toa_pfwNlNotchStDevEst);
        db.update(groupIdx | 0x07, m_tipoffModelTestPoints.toa_pfwNlNotchMeanEst);
        db.update(groupIdx | 0x08, m_tipoffModelTestPoints.toa_pfwSecLatch);
        db.update(groupIdx | 0x09, m_tipoffModelTestPoints.toa_lwLpfPost);
        db.update(groupIdx | 0x0A, m_tipoffModelTestPoints.toa_targetPayloadFinal);
        db.update(groupIdx | 0x0B, m_tipoffModelTestPoints.toa_targetPayloadStatus);
        db.update(groupIdx | 0x0C, m_tipoffModelTestPoints.toa_sendPayloadArb);
        db.update(groupIdx | 0x0D, m_tipoffModelTestPoints.toa_imu_cal_pitch_angle);
        db.update(groupIdx | 0x0E, m_tipoffModelTestPoints.toa_appNumber);
        db.update(groupIdx | 0x0F, m_tipoffModelTestPoints.toa_tiltBoreDia);
        db.update(groupIdx | 0x10, m_tipoffModelTestPoints.toa_tiltNumCyl);
        db.update(groupIdx | 0x11, m_tipoffModelTestPoints.toa_tiltRodDia);
        db.update(groupIdx | 0x12, m_tipoffModelTestPoints.toa_liftBoreDia);
        db.update(groupIdx | 0x13, m_tipoffModelTestPoints.toa_liftRodDia);
        db.update(groupIdx | 0x14, m_tipoffModelTestPoints.toa_ratedPayload);
        db.update(groupIdx | 0x15, m_tipoffModelTestPoints.toa_toolBcLength);
        db.update(groupIdx | 0x16, m_tipoffModelTestPoints.toa_payloadAncZeroed);
        db.update(groupIdx | 0x17, m_tipoffModelTestPoints.toa_payloadAncAdjusted);

        db.update(groupIdx | 0x18, m_tipoffModelTestPoints.toa_pfwSecPayload);
        db.update(groupIdx | 0x19, m_tipoffModelTestPoints.toa_pfwSecStatus);
        db.update(groupIdx | 0x1A, m_tipoffModelTestPoints.toa_pfwSecStDev);
        db.update(groupIdx | 0x1B, m_tipoffModelTestPoints.toa_pfwNlStDevEst);
        db.update(groupIdx | 0x1C, m_tipoffModelTestPoints.toa_pfwUnsecStatus);
        db.update(groupIdx | 0x1D, m_tipoffModelTestPoints.toa_pfwUnsecBoundLower);
        db.update(groupIdx | 0x1E, m_tipoffModelTestPoints.toa_pfwUnsecBoundUpper);
        db.update(groupIdx | 0x1F, m_tipoffModelTestPoints.toa_lwSpillRate);
        db.update(groupIdx | 0x20, m_tipoffModelTestPoints.toa_lwStatus);
        db.update(groupIdx | 0x21, m_tipoffModelTestPoints.toa_rawDist);
        db.update(groupIdx | 0x22, m_tipoffModelTestPoints.toa_rawPayload);
        db.update(groupIdx | 0x23, m_tipoffModelTestPoints.toa_payloadZeroed);
        db.update(groupIdx | 0x24, m_tipoffModelTestPoints.toa_pfwIsWarm);
        db.update(groupIdx | 0x25, m_tipoffModelTestPoints.toa_pfwSecIsSecure);
        db.update(groupIdx | 0x26, m_tipoffModelTestPoints.toa_pfwSecIsNoSliding);
        db.update(groupIdx | 0x27, m_tipoffModelTestPoints.toa_pfwSecIsNoCollapsing);
        db.update(groupIdx | 0x28, m_tipoffModelTestPoints.toa_pfwSecIsRacked);
        db.update(groupIdx | 0x29, m_tipoffModelTestPoints.toa_pfwSecMinBucketAng);
        db.update(groupIdx | 0x2A, m_tipoffModelTestPoints.toa_pfwMcOk);
        db.update(groupIdx | 0x2B, m_tipoffModelTestPoints.toa_pfwMcMaybeStalled);
        db.update(groupIdx | 0x2C, m_tipoffModelTestPoints.toa_pfwMcMaybeRackStall);
        db.update(groupIdx | 0x2D, m_tipoffModelTestPoints.toa_pfwMcMaybeGrounded);
        db.update(groupIdx | 0x2E, m_tipoffModelTestPoints.toa_statPayloadNlNotchOneUp);
        db.update(groupIdx | 0x2F, m_tipoffModelTestPoints.toa_statPayloadNlNotchOneLow);
        db.update(groupIdx | 0x30, m_tipoffModelTestPoints.toa_statPayloadNlNotchOneSize);
        db.update(groupIdx | 0x31, m_tipoffModelTestPoints.toa_statPayloadNlNotchTwoUp);
        db.update(groupIdx | 0x32, m_tipoffModelTestPoints.toa_statPayloadNlNotchTwoLow);
        db.update(groupIdx | 0x33, m_tipoffModelTestPoints.toa_statPayloadNlNotchTwoSize);
        db.update(groupIdx | 0x34, m_tipoffModelTestPoints.toa_statPayloadNlOneUp);
        db.update(groupIdx | 0x35, m_tipoffModelTestPoints.toa_statPayloadNlOneLow);
        db.update(groupIdx | 0x36, m_tipoffModelTestPoints.toa_statPayloadNlOneSize);
        db.update(groupIdx | 0x37, m_tipoffModelTestPoints.toa_statPayloadNlTwoUp);
        db.update(groupIdx | 0x38, m_tipoffModelTestPoints.toa_statPayloadNlTwoLow);
        db.update(groupIdx | 0x39, m_tipoffModelTestPoints.toa_statPayloadNlTwoSize);
        db.update(groupIdx | 0x3A, m_tipoffModelTestPoints.toa_pfwNlMeanEst);
        db.update(groupIdx | 0x3B, m_tipoffModelTestPoints.toa_pfwPayloadFiltFinal);
        db.update(groupIdx | 0x3C, m_tipoffModelTestPoints.toa_pfwPayloadNotchFiltFinal);
        db.update(groupIdx | 0x3D, m_tipoffModelTestPoints.toa_pfwPayloadNotchPost);
        db.update(groupIdx | 0x3E, m_tipoffModelTestPoints.toa_pfwLatchInvalidate);
        db.update(groupIdx | 0x3F, m_tipoffModelTestPoints.toa_imuRawEefAcclX);
        db.update(groupIdx | 0x40, m_tipoffModelTestPoints.toa_imuRawEefAcclY);
        db.update(groupIdx | 0x41, m_tipoffModelTestPoints.toa_imuRawEefAcclZ);
        db.update(groupIdx | 0x42, m_tipoffModelTestPoints.toa_imuNeefGravX);
        db.update(groupIdx | 0x43, m_tipoffModelTestPoints.toa_imuNeefGravY);
        db.update(groupIdx | 0x44, m_tipoffModelTestPoints.toa_imuNeefGravZ);
        db.update(groupIdx | 0x45, m_tipoffModelTestPoints.toa_imuNeefPitch);
        db.update(groupIdx | 0x46, m_tipoffModelTestPoints.toa_targetCompMargin);
        db.update(groupIdx | 0x47, m_tipoffModelTestPoints.toa_targetPayloadPostComp);
        db.update(groupIdx | 0x48, m_tipoffModelTestPoints.toa_targetPayloadPreComp);
        db.update(groupIdx | 0x49, m_tipoffModelTestPoints.toa_statPayloadSecureTwoSize);
        db.update(groupIdx | 0x4A, m_tipoffModelTestPoints.toa_statPayloadSecureOneUpper);
        db.update(groupIdx | 0x4B, m_tipoffModelTestPoints.toa_statPayloadSecureOneLower);
        db.update(groupIdx | 0x4C, m_tipoffModelTestPoints.toa_statPayloadSecureOneSize);
        db.update(groupIdx | 0x4D, m_tipoffModelTestPoints.toa_statPayloadSecureTwoUpper);
        db.update(groupIdx | 0x4E, m_tipoffModelTestPoints.toa_statPayloadSecureTwoLower);
        db.update(groupIdx | 0x4F, m_tipoffModelTestPoints.toa_sendCpmLivePayload);
        db.update(groupIdx | 0x4F, m_tipoffModelTestPoints.toa_toolBcAngle);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 13xxxx - AutonomyConditionsDiagnosticsTX */
    if ( m_autonomyConditionDiagnosticsTxChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 19;
        static constexpr uint32_t groupIdx = index << 16;

        db.update(groupIdx | 0x00, m_autonomyConditionDiagnosticsTxChannel.displayEthernetBad);
        db.update(groupIdx | 0x01, m_autonomyConditionDiagnosticsTxChannel.productLinkEthernetBad);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 14xxxx - BEMSimMgrState */
    if ( m_BemSimDebugChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 20;
        static constexpr uint32_t groupIdx = index << 16;
        // Added for BEM Simulator
        db.update(groupIdx | 0x00, m_BemSimDebugChannel.cnfg.chargeMode);
        db.update(groupIdx | 0x01, m_BemSimDebugChannel.cnfg.startCharge);
        db.update(groupIdx | 0x02, m_BemSimDebugChannel.totalFuelUsed);
        db.update(groupIdx | 0x03, m_BemSimDebugChannel.cnfg.lastDischargeRate);
        db.update(groupIdx | 0x04, m_BemSimDebugChannel.cnfg.bemSimEnabled);
        db.update(groupIdx | 0x05, m_BemSimDebugChannel.cnfg.chargerCapacity);
        db.update(groupIdx | 0x06, m_BemSimDebugChannel.cnfg.engineDerateEnabled);
        db.update(groupIdx | 0x07, m_BemSimDebugChannel.chargeLevel);
        db.update(groupIdx | 0x08, m_BemSimDebugChannel.dischargeRate);
        db.update(groupIdx | 0x09, m_BemSimDebugChannel.derateEngineCmd);
        db.update(groupIdx | 0x0A, m_BemSimDebugChannel.derateEngineRPM);
        db.update(groupIdx | 0x0B, m_BemSimDebugChannel.chargeRate);
        db.update(groupIdx | 0x0C, m_BemSimDebugChannel.timeToCharged);
        db.update(groupIdx | 0x0D, m_BemSimDebugChannel.timeToDischarged);

        db.update(groupIdx | 255, updateCounter++);

    }

    { /* index group: 15xxxx - Datalink Inputs */
        static constexpr uint32_t index = 21;
        static constexpr uint32_t groupIdx = index << 16;

        static uint8_t tirePressureReceiverAmbientRFLevel = 0;
        static uint8_t tireLocation = 0;
        static uint8_t tireRefPressure = 0; // 8 kPa/bit
        static uint8_t tirePressure = 0; // 8 kPa/bit
        static uint8_t tireInfoAge = 255; // 1 minute/bit
        static uint8_t tireRFSignal = 127; // log2 RF level 1 count/bit
        static uint32_t tireSensorSN = 0;

        bool receivedData = false;

        if (nullptr != dataLinkDataInput) {
            DataLinkData dlData;
            while (dataLinkDataInput->get(dlData)) {
                for (auto& dlParam : dlData.GetParams()) {
                    // Look for tire pressure monitoring receiver data parameter
                    if ((DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID == dlParam.GetParamIdentifierType()) &&
                            (0x0800 == dlParam.GetParamId()) &&
                            (dlParam.IsPIDDataReceived())) {

                        // We have received new information about this pid
                        if (0 == dlParam.GetLastValueDsi()) {
                            const std::vector<unsigned_8>& data = dlParam.GetLastGoodValueVector();
                            if (data.size() >= 7) {
                                //AIS_LOG_ALERT("Length = %d, Ambient RF Level = %d", data.size(), data[4]);
                                //AIS_LOG_ALERT("%d, %d, %d, %d, %d, %d, %d", data[0], data[1], data[2], data[3], data[4], data[5], data[6]);
                                tirePressureReceiverAmbientRFLevel = data[4];
                                receivedData = true;
                            }
                            else {
                                //AIS_LOG_ALERT("Length = %d", data.size());
                                tirePressureReceiverAmbientRFLevel = 0;
                                receivedData = true;
                            }
                        }
                        else {
                            //AIS_LOG_ALERT("We have a DSI for tire monitoring data = %d.", dlParam->GetLastValueDsi());
                            tirePressureReceiverAmbientRFLevel = 0;
                            receivedData = true;
                        }
                    }

                    // Look for the Tire Pressure Reference Information - TPRI PGN
                    else if ((DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN == dlParam.GetParamIdentifierType()) &&
                            (64953 == dlParam.GetParamId()) &&
                            (dlParam.IsPIDDataReceived()) &&
                            (VarLengthDataLinkParamPool::PGN == dlParam.GetVarLengthParamType())) {
                        uint16_t dsi = dlParam.GetLastValueDsi();
                        uint8_t len = dlParam.GetVarParamBlockLength();
                        const uint8_t* data = dlParam.GetVarParamBlock();

                        if ((nullptr != data) && (DataLinkParam::DSI_CODE_OK() == dsi) && (len >= 8)) {
                            OEL_UNPACK_LE_8(data, tireLocation);
                            OEL_UNPACK_LE_8(data, tireRefPressure);
                            OEL_UNPACK_LE_8(data, tirePressure);
                            OEL_UNPACK_LE_8(data, tireInfoAge);
                            OEL_UNPACK_LE_8(data, tireRFSignal);
                            tireRFSignal = tireRFSignal & 0x7F;
                            OEL_UNPACK_LE_24(data, tireSensorSN);
                        }
                        else {
                            // Problem
                            tireLocation = 0;
                            tireRefPressure = 0;
                            tirePressure = 0;
                            tireInfoAge = 255;
                            tireRFSignal = 127;
                            tireSensorSN = 0;
                        }
                        receivedData = true;
                    }
                }
            }
        }

        if ((!init_done) || (receivedData)) {
            static int updateCounter = 0;
            db.update(groupIdx | 0x00, tirePressureReceiverAmbientRFLevel);
            db.update(groupIdx | 0x01, tireLocation);
            db.update(groupIdx | 0x02, tireRefPressure);
            db.update(groupIdx | 0x03, tirePressure);
            db.update(groupIdx | 0x04, tireInfoAge);
            db.update(groupIdx | 0x05, tireRFSignal);
            db.update(groupIdx | 0x06, tireSensorSN);
            db.update(groupIdx | 255, updateCounter++);
        }
    }

    /* mark init done */
    if (!init_done) {
        init_done = true;
    }

    return retVal;
  }

  ///////////////////////////////////////////////////////////////////////////////
  /// @brief Run "initReadInterface" on all of the scs channels in the structure
  ///
  /// @return true if all interfaces were successfully configured, false if any failed
  ///////////////////////////////////////////////////////////////////////////////
  bool initReadInterface( ConfigSection& cs )
  {
    bool retVal = true;

    if (!m_systemHardwareHealth.initReadInterface("SystemHardwareHealthInput", cs)) {
        retVal = false;
    }

    if ( !m_lpsSaWeighReqstChannel.initReadInterface("LpsSaWeighReqstChannelInput", cs) ) retVal = false;
    if ( !m_lpsSaWeighRespChannel.initReadInterface("LpsSaWeighRespChannelInput", cs) ) retVal = false;
    if ( !m_lpsSaWeighTxChannel.initReadInterface("LpsSaWeighTxChannelInput", cs) ) retVal = false;
    if ( !m_lpsSaWeighDebugChannel.initReadInterface("LpsSaWeighDebugChannelInput", cs) ) retVal = false;
    if ( !m_lpsSaWeighInitDebugChannel.initReadInterface("LpsSaWeighInitDebugChannelInput", cs) ) retVal = false;
    if ( !m_lpsSaNvmDataChannel.initReadInterface("LpsSaNvmCalDataChannelInput", cs) ) retVal = false;
    if ( !m_lpsSaNvmOnTheFlyDataChannel.initReadInterface("LpsSaNvmCalOnTheFlyDataChannelInput", cs) ) retVal = false;
    if ( !m_lpsSaJobMgrTxChannel.initReadInterface("LpsSaJobMgrTxChannelInput", cs) ) retVal = false;
    if ( !m_pwmInputChannels.initReadInterface("PwmInputChannelsInput", cs) ) retVal = false;
    if ( !m_machine.initReadInterface("MachineInput", cs) ) retVal = false;
    if ( !m_lpsSaJobMgrReqstChannel.initReadInterface("LpsSaJobMgrReqstChannelInput", cs) ) retVal = false;
    if ( !m_lpsSaJobMgrRespChannel.initReadInterface("LpsSaJobMgrRespChannelInput", cs) ) retVal = false;
    if ( !m_lpsSaJobMgrDebugChannel.initReadInterface("LpsSaJobMgrDebugChannelInput", cs) ) retVal = false;
    if ( !m_switchInputScs.initReadInterface("SwitchInputScsInput", cs) ) retVal = false;
    if ( !m_cycleSegTxData.initReadInterface("CycleSegTxChannelInput", cs)) retVal = false;
    if ( !m_workOrderAssistTxChannel.initReadInterface("WorkOrderAssistTxInput", cs) ) retVal = false;
    if ( !m_tipoffModelTestPoints.initReadInterface("TipoffModelTestPointsInput", cs) ) retVal = false;
    if ( !m_autonomyConditionDiagnosticsTxChannel.initReadInterface("AutonomyConditionDiagnosticsTxInput", cs) ) retVal = false;
    if ( !m_BemSimDebugChannel.initReadInterface("BEMSimStateInput", cs) ) retVal = false;

    if (!m_displayStateChannel.initReadInterface("DisplayStateInput", cs)) {
        retVal = false;
    }
    if ( !m_widgetsDebugdata.initReadInterface("WidgetsDebugDataInput", cs) ) retVal = false;
    if ( !m_BemSimDebugChannel.initReadInterface("BEMSimStateInput", cs) ) { retVal = false; }

    if(!task::InterfaceDb::bind("DataLinkDataInput", dataLinkDataInput)) {
        AIS_LOG_ERROR("DataLinkDataInput Interface not configured.");
        retVal = false;
    }

    return retVal;
  }

};

#endif /*XCPSCSINPUTS_H_*/
