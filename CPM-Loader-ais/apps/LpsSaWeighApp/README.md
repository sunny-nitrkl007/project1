# LpsSaWeighApp - Architecture, Channel-Wise Migration & Conversion Guide

## Overview

`LpsSaWeighApp` is the core payload calculation and linkage measurement engine for the Loader Payload System (LPS). It is responsible for:
- Reading hydraulic pressures, rotary/in-cylinder linkage position sensors, and chassis IMU telemetry.
- Performing dynamic bucket payload weighing, tip-off assist (TOA) adjustments, and zeroing algorithms.
- Managing linkage calibration tables (Lift, Tilt, Payload/Span calibration).
- Tracking Legal-For-Trade (LFT) seal configurations, component serial IDs, and software part numbers.
- Enforcing software flash enabler rules during calibration and sealed operating modes.

This application has been migrated from legacy **AIS SCS (Shared Memory Communication Service)** to **ROS2 / DDS** using `ros2wrapper` (`RosInputInterface` and `RosOutputInterface`).

---

## Summary of Channel-Wise Changes

The following table summarizes all communication channels updated or utilized by `LpsSaWeighApp`, contrasting legacy AIS SCS interfaces with their modernized ROS2 counterparts.

| Channel Name | Direction | Old Implementation (AIS SCS) | New Implementation (ROS2) | Topic / Message Type | Summary of Changes |
|---|---|---|---|---|---|
| **`LpsSaWeighTxChannel`** | Output | `LpsSaWeighTxChannelOutput* LpsSaWeighScsTxOut` (via `InterfaceDb::bind`) | `RosOutputInterface<cpm_common_interfaces::msg::LpsSaWeighTxChannel>* LpsSaWeighScsTxOut_ROS2` | `lps_sa_weigh_tx_channel`<br>`cpm_common_interfaces::msg::LpsSaWeighTxChannel` | Full payload telemetry output. Removed raw SCS dual-publish path; publishes exclusively over ROS2. Transforms sensor values, IMU pitch/roll, bitmask indicators, and LFT seal tracking data into ROS2 message. |
| **`LpsSaWeighReqstChannel`** | Input | `LpsSaWeighReqstChannelInput*` (via `InterfaceDb::bind`) | `RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>* LpsSaWeighScsReqstIn` | `lps_sa_weigh_reqst_channel`<br>`cpm_common_interfaces::msg::LpsSaWeighReqstChannel` | Ingests requests and commands (Zero, Reweigh, Calibrate, Clear Warning, Set Target, Store) over ROS2. |
| **`LpsSaWeighRespChannel`** | Output | `LpsSaWeighRespChannelOutput* LpsSaWeighScsRespOut` (via `InterfaceDb::bind`) | `RosOutputInterface<cpm_common_interfaces::msg::LpsSaWeighRespChannel>* LpsSaWeighScsRespOut_ROS2` | `lps_sa_weigh_resp_channel`<br>`cpm_common_interfaces::msg::LpsSaWeighRespChannel` | Publishes execution results, status flags, and timestamps back to callers for each received weigh command. |
| **`LpsSaJobMgrTxChannel`** | Input | `LpsSaJobMgrTxChannelInput* LpsSaJobMgrScsTxIn` (via `InterfaceDb::bind`) | `RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>* LpsSaJobMgrTxRosIn_` | `lps_sa_job_mgr_tx_channel`<br>`job_mgr_interfaces::msg::LpsSaJobMgrTxChannel` | Subscribes to Job Manager state to sync pass counts, truck target weights, standby states, tip-off activation flags, and calibration factors. |
| **`LpsSaJobMgrReqstChannel`** | Output | `LpsSaJobMgrReqstChannelOutput* LpsSaJobMgrScsReqstOut` (via `InterfaceDb::bind`) | `RosOutputInterface<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>* LpsSaJobMgrReqstRosOut_` | `lps_sa_job_mgr_reqst_channel`<br>`cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel` | Dispatches job management commands (such as automated Zero requests via `LpsSaScsSendZeroRqst()`) to Job Manager over ROS2. |
| **`LpsSaWeighInitDebugChannel`** | Output | `LpsSaWeighInitDebugChannelOutput* LpsSaWeighScsInitDebugOut` (via `InterfaceDb::bind`) | `RosOutputInterface<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel>* LpsSaWeighInitDebugRosOut_` | `lps_sa_weigh_init_debug_channel`<br>`weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel` | Publishes initialization debug data and machine-specific configuration tables over ROS2 upon task startup. |
| **`LpsSaWeighDebugChannel`** | Output | `LpsSaWeighDebugChannelOutput* LpsSaWeighScsDebugOut` (via `InterfaceDb::bind`) | `RosOutputInterface<weigh_app_interfaces::msg::LpsSaWeighDebugChannel>* LpsSaWeighDebugRosOut_` | `lps_sa_weigh_debug_channel`<br>`weigh_app_interfaces::msg::LpsSaWeighDebugChannel` | Publishes detailed internal weighing algorithm state, WRW table results, stall detect flags, filtered lift positions, and Tip-Off Assist inputs/outputs (`TipoffAssistInputs`, `TipoffAssistOutputs`) over ROS2. |
| **`CalMgrCmdReqst`** | Input | `CalMgrCmdReqstInput* LpsCalCmdScsReqstIn` (via `InterfaceDb::bind`) | `rclcpp::Subscription<weigh_app_interfaces::msg::CalMgrCmdReqst>::SharedPtr calCmdReqstSub_` | `cal_mgr_cmd_reqst`<br>`weigh_app_interfaces::msg::CalMgrCmdReqst` | Ingests calibration commands (Empty/Full bucket calibration, cal iterm bitmasks) from Autonomy Condition Diagnostics (ACD) over ROS2 via `LpsSaWeighCalReqstCallback`. |
| **`CalMgrCmdResp`** | Output | `CalMgrCmdRespOutput* LpsCalCmdScsRespOut` (via `InterfaceDb::bind`) | `RosOutputInterface<weigh_app_interfaces::msg::CalMgrCmdResp>* calCmdRespRosOut_` | `cal_mgr_cmd_resp`<br>`weigh_app_interfaces::msg::CalMgrCmdResp` | Publishes calibration command results (`CAL_MGR_MR_SUCCESS_SAVED`, `CAL_MGR_MR_FAIL`, etc.) back to ACD over ROS2. |
| **`LpsSaNvmCalDataChannel`** | Output | `LpsSaNvmCalDataChannelOutput* LpsNvmDumpChanOut` (via `InterfaceDb::bind`) | `RosOutputInterface<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel>* LpsNvmCalRosOut_` | `lps_sa_nvm_cal_data_channel`<br>`weigh_app_interfaces::msg::LpsSaNvmCalDataChannel` | Serializes and publishes key-on NVM calibration parameters (raise/lower slow/fast pressure curves, speeds, stop angles, and IMU calibration results) over ROS2. |
| **`LpsSaNvmCalOnTheFlyDataChannel`** | Output | `LpsSaNvmCalOnTheFlyDataChannelOutput* LpsNvmOnTheFlyDumpChanOut` (via `InterfaceDb::bind`) | `RosOutputInterface<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel>* LpsNvmCalOnTheFlyRosOut_` | `lps_sa_nvm_cal_on_the_fly_data_channel`<br>`weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel` | Publishes real-time on-the-fly dynamic calibration calculation metrics over ROS2. |
| **`ReadyToFlashStatus`** | Output | `ReadyToFlashStatusOutput* ReadyToFlashStatusOutput` (via `InterfaceDb::bind`) | `RosOutputInterface<weigh_app_interfaces::msg::ReadyToFlashStatus>* ReadyToFlashStatusRosOut_` | `ready_to_flash_status`<br>`weigh_app_interfaces::msg::ReadyToFlashStatus` | Publishes flash authorization status (e.g. `APP_READY_CODE_OK_TO_FLASH` or blocking when LFT is sealed and flash disabled). |
| **`DemoAppTxChannel`** | Input | `DemoAppTxChannelInput* DemoAppTxIn` (via `InterfaceDb::bind`) | `RosInputInterface<weigh_app_interfaces::msg::DemoAppTxChannel>* DemoAppTxRosIn_` | `demo_app_tx_channel`<br>`weigh_app_interfaces::msg::DemoAppTxChannel` | Ingests simulated linkage angles (`angle_lift_demo`, `angle_abc_demo`) and cylinder pressures during demo/playback mode. |
| **`PartNumbers`** | Input | `PartNumbersInput* PartNumbersInput_` (via `InterfaceDb::bind`) | `RosInputInterface<weigh_app_interfaces::msg::PartNumbers>* PartNumbersRosIn_` | `part_numbers`<br>`weigh_app_interfaces::msg::PartNumbers` | Reads Product ID, Software Group Part Numbers, and Equipment IDs; triggers logging to `product_id.txt` on change. |
| **`SystemHardwareHealth`** | Input | `SystemHardwareHealthInput* SystemHardwareHealthInput_` (via `InterfaceDb::bind`) | `RosInputInterface<weigh_app_interfaces::msg::SystemHardwareHealthStorage>* SystemHardwareHealthRosIn_` | `system_hardware_health`<br>`weigh_app_interfaces::msg::SystemHardwareHealthStorage` | Ingests hardware status data (battery voltages, sensor health) to trigger low-voltage diagnostics and fault conditions. |
| **`SystemHardwareHealthRequest`** | Output | `SCSOutData<SystemHardwareHealthRequest> SystemHardwareHealthRequestOutput_` | `RosOutputInterface<weigh_app_interfaces::msg::SystemHardwareHealthRequest>* SystemHardwareHealthRequestRosOut_` | `system_hardware_health_request`<br>`weigh_app_interfaces::msg::SystemHardwareHealthRequest` | Periodically publishes polling request triggers over ROS2 to query hardware health monitors. |

---

## Channels Retained on AIS SCS / Internal Interfaces

The following subsystem channels continue to interface directly with local board/driver modules:
- **`DisplayStateInput`**: UI display mode and verification states.
- **`PrinterCnfgInput`**: Ticket printer settings.
- **`DataLinkDataInput`**: Direct datalink PIDs.
- **`AutonomyConditionDiagnosticsTxChannelInput`**: SEA license evaluation.
- **`ShmClockInput`**: Clock synchronization.
- **`PwmInputChannelsInput` & `MachineInput`**: Direct hardware PWM and machine signals.
- **`AisJhm2TxChannelInput`**: JHM2 telemetry input.

---

## Complex Conversion & Transformation Logic

### 1. `LpsSaWeighTxChannel` Conversion Details

The payload telemetry message bridges complex mathematical models and bitmasks into the ROS2 representation:

- **Timestamps**:
  `txOut.time_point_ns` is captured in steady clock nanoseconds:
  ```cpp
  txOut.time_point_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
      std::chrono::steady_clock::now().time_since_epoch()).count();
  ```
- **Bitmask Conversion (`std::bitset` &rarr; `uint32_t` / `uint16_t`)**:
  - `event_state.bits`: Converted from `std::bitset<ACDEventPopUp::NUM_BITS>` via `.to_ulong()`.
  - `diag_state.bits`: Converted from `std::bitset<ACDDiagPopUp::NUM_BITS>` via `.to_ulong()`.
  - `info_state.bits`: Converted from `std::bitset<ACDInfoPopUp::NUM_BITS>` via `.to_ulong()`.
  - `pid_data.prod_measure_weigh_status`: Packed from `ACDWeighStatus::type` bitmask representing condition states (stalls, reweigh speed changing, excessive pitch, warmup lifts).
- **IMU & Angle Transformations**:
  - Linear accelerations ($x, y, z$) are scaled by $100.0$ and clamped into INT16 PID values (`TO_INT16_PID(accel * 100.f)`).
  - Machine pitch degrees and pitch grade are scaled by $10.0$ (`TO_INT16_PID(deg * 10.f)`).
  - Machine rear roll and roll grade are converted using coordinate transformation conventions:
    ```cpp
    txOut.pid_data.machine_rear_roll = TO_INT16_PID(chassisImu_.imu.rollDegrees() * 100.f);
    txOut.pid_data.machine_rear_side_slope = TO_INT16_PID(chassisImu_.imu.rollGrade() * 10.f);
    txOut.pid_data.machine_roll = txOut.pid_data.machine_rear_roll;
    txOut.pid_data.machine_side_slope = TO_INT16_PID(-txOut.pid_data.machine_rear_side_slope);
    ```
  - If the IMU is unavailable (`!chassisImu_.imuOk`), acceleration, pitch, and roll values are assigned error flags `UNKNOWN2S + FMICNM` (Data Specific Indicator).
- **LFT Seal Status & Component Hardware Tracking**:
  - `sealTracker_.getSealStatus()` converts seal timestamp to `seal_time_ns` and copies `seal_id`.
  - Serial numbers and component IDs are serialized: `lift_position_sensor_id`, `tilt_position_sensor_id`, `imu_sensor_id`, `work_tool_id`, `implement_serial_num`.

### 2. Job Manager State Synchronisation (`LpsJobMgrTxRead`)

- On every cycle, `LpsSaJobMgrTxRosIn_` drains incoming messages to keep track of:
  - `pass_count`, `truck_target_weight`, `truck_start_weight`.
  - `tip_off_state` and `standby_state`.
  - **Simple Calibration Sync**: If a new load cycle starts (`passCount == 0` and `subtotal_count == 1`), new calibration factors (`updatedSimpleCalFactor`) are committed to NVM and propagated to `LpsSetCalAdjustFactor()`.
  - **Tip-Off Activation Handling**: If `tipoff_active` transitions from inactive to active, digging is immediately concluded via `LpsWeighEndDig()`.

### 3. Flash Enabler Rule Engine (`flashEnablerUpdate`)

- Evaluates whether software flashing can be authorized:
  - Default status: `APP_READY_CODE_OK_TO_FLASH`.
  - If Legal-For-Trade is enabled, the unit is cryptographically/mechanically sealed, and flash override is disabled (`!cnfg_.flashEnabled`), the ready code is set to:
    `APP_READY_CODE_PAYLOAD_LEGAL_FOR_TRADE_IS_SEALED`
- Publishes the resulting state on topic `ready_to_flash_status` via `ReadyToFlashStatusRosOut_`.

---

## Architectural & Integration Notes

- **Removal of Dual-Publishing**: Previously, `LpsSaWeighApp` dual-published telemetry and responses on both SCS and ROS2. This has been cleaned up so that `LpsSaWeighApp` communicates strictly over ROS2.
- **Interoperability via Bridge**: Communication with any remaining legacy SCS processes (such as `LpsSaTotalsApp` or `WorkOrderAssistApp`) is maintained seamlessly through `ScsToRos2Bridge`.
