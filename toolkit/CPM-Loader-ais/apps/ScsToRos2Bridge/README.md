# ScsToRos2Bridge

## Overview

`ScsToRos2Bridge` is a standalone AIS task providing bidirectional message forwarding between legacy **AIS SCS (Shared Memory Communication Service)** tasks and modernized **ROS2 / DDS** microservices (`LpsSaJobMgrApp` and `LpsSaWeighApp`).

Each channel is bridged in **exactly one direction** per channel flow to guarantee deterministic operation and prevent communication feedback loops.

---

## Channel-Wise Bridging Summary

The bridge provides conversion and data forwarding across **28 channel interfaces** (15 AIS SCS &rarr; ROS2, 13 ROS2 &rarr; AIS SCS):

| Channel Name | Direction | AIS SCS Interface | ROS2 Interface / Topic | Message Type | Description & Purpose |
|---|---|---|---|---|---|
| **`LpsSaJobMgrReqstChannel`** | `AIS SCS -> ROS2` | `LpsSaJobMgrReqstChannelInput` | `lps_sa_job_mgr_reqst_channel` | `cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel` | Forwards Job Manager commands and requests from legacy SCS producers (`WorkOrderAssistApp`, `hornOnStoreTest`, `AisJhm2RequestProcessor`) to ROS2 `LpsSaJobMgrApp`. |
| **`LpsSaJobMgrRespChannel`** | `ROS2 -> AIS SCS` | `LpsSaJobMgrRespChannelOutput` | `lps_sa_job_mgr_resp_channel` | `job_mgr_interfaces::msg::LpsSaJobMgrRespChannel` | Relays Job Manager command acknowledgements and status back to SCS consumers (`AutonomyConditionDiagnostics`, `aisXcpServer`, `AisJhm2RequestProcessor`). |
| **`AisJhm2TxChannel`** | `AIS SCS -> ROS2` | `AisJhm2TxChannelInput` | `ais_jhm2_tx_channel` | `cpm_common_interfaces::msg::AisJhm2TxChannel` | Forwards JHM2 truck dispatch state to ROS2 `LpsSaJobMgrApp` to trigger simple calibration cleanup. |
| **`SwitchInputScs`** | `AIS SCS -> ROS2` | `SwitchInputScsInput` | `switch_input_scs` | `job_mgr_interfaces::msg::SwitchInputScs` | Forwards physical digital switch states (STG states, store buttons, zero requests) from `SwitchInputApp` to ROS2. |
| **`LpsSaLoadRecordChannel`** | `ROS2 -> AIS SCS` | `LoadRecordOutput` | `lps_sa_load_record_channel` | `job_mgr_interfaces::msg::LpsSaLoadRecordChannel` | Converts finalized ROS2 load records and subtotals to SCS datum for legacy consumers (`LpsSaTotalsApp`, `WorkOrderAssist`, etc.). |
| **`LpsSaWeighReqstChannel`** | `AIS SCS -> ROS2` | `LpsSaWeighReqstChannelInput` | `lps_sa_weigh_reqst_channel` | `cpm_common_interfaces::msg::LpsSaWeighReqstChannel` | Forwards payload weighing requests (zero, reweigh, calibrate, store) from legacy SCS clients to ROS2 Weigh subsystem. |
| **`LpsSaWeighRespChannel`** | `ROS2 -> AIS SCS` | `LpsSaWeighRespChannelOutput` | `lps_sa_weigh_resp_channel` | `cpm_common_interfaces::msg::LpsSaWeighRespChannel` | Transmits weigh system command execution results and acknowledgements back to SCS consumers. |
| **`LpsSaWeighTxChannel`** | `ROS2 -> AIS SCS` | `LpsSaWeighTxChannelOutput` | `lps_sa_weigh_tx_channel` | `cpm_common_interfaces::msg::LpsSaWeighTxChannel` | Full weighing telemetry bridge: loads, pressures, link positions, CAN PIDs, indicator states, and pitch/roll sensors. |
| **`ShmClock`** | `AIS SCS -> ROS2` | `ShmClockInput` | `shm_clock_input` | `cpm_common_interfaces::msg::ShmClockInput` | Forwards Service Hour Meter (SHM) seconds, UTC offset minutes, and timezone strings to ROS2 nodes. |
| **`DisplayStateInput`** | `AIS SCS -> ROS2` | `DisplayStateInput` | `lps_sa_ui_display_state_interface` | `cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface` | Forwards UI display state and verification mode flags to ROS2 subscribers. |
| **`DataLinkData`** | `AIS SCS -> ROS2` | `DataLinkDataInput` | `data_link_data` | `job_mgr_interfaces::msg::DataLinkData` | Bridges reduced J1939 / CAN datalink PID fields used by JobMgr (store buttons, tip-off signals, manual adds) to ROS2. |
| **`WeighAppDataLinkData`** | `AIS SCS -> ROS2` | `DataLinkDataInput` | `weigh_app_data_link_data` | `weigh_app_interfaces::msg::DataLinkData` | Bridges full-fidelity datalink fields used by WeighApp, including SID, identifier type, raw typed values, engineering values, scaling, offset, units, variable PGN/CAT EXT blocks, and DSI. |
| **`AutonomyConditionDiagnosticsTx`** | `AIS SCS -> ROS2` | `AutonomyConditionDiagnosticsTxChannelInput` | `autonomy_condition_diagnostics_tx_channel` | `cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel` | Bridges SEA feature license statuses (Essentials, Pro, Legal-for-Trade) to ROS2 nodes. |
| **`EventDiagnosticData`** | `AIS SCS -> ROS2` | `EventDiagnosticDataInput` | `event_diagnostic_data` | `job_mgr_interfaces::msg::EventDiagnosticData` | Bridges active diagnostic fault codes, event statuses, and TOA EIDs to ROS2 nodes. |
| **`LpsSaJobMgrTxChannel`** | `ROS2 -> AIS SCS` | `LpsSaJobMgrTxChannelOutput` | `lps_sa_job_mgr_tx_channel` | `job_mgr_interfaces::msg::LpsSaJobMgrTxChannel` | Forwards ROS2 Job Manager state, active task information, and weights to legacy SCS UI and telemetry clients. |
| **`LpsSaJobMgrDebugChannel`** | `ROS2 -> AIS SCS` | `LpsSaJobMgrDebugChannelOutput` | `lps_sa_job_mgr_debug_channel` | `job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel` | Relays pass tracker state and tip-off assist activation counts to legacy SCS debug tools. |
| **`OutputChannel`** | `ROS2 -> AIS SCS` | `OutputChannelOutput` | `output_channel` | `job_mgr_interfaces::msg::OutputChannel` | Bridges discrete hardware output activations (e.g., horn-on-store pulse sequences) from ROS2 to SCS hardware drivers. |
| **`LpsSaWeighInitDebugChannel`** | `ROS2 -> AIS SCS` | `LpsSaWeighInitDebugChannelOutput` | `lps_sa_weigh_init_debug_channel` | `weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel` | Forwards Weigh subsystem initialization diagnostics to legacy SCS debug sinks. |
| **`LpsSaWeighDebugChannel`** | `ROS2 -> AIS SCS` | `LpsSaWeighDebugChannelOutput` | `lps_sa_weigh_debug_channel` | `weigh_app_interfaces::msg::LpsSaWeighDebugChannel` | Forwards detailed internal weighing algorithm debug data, WRW tables, and TOA inputs/outputs to legacy SCS/XCP tools. |
| **`LpsSaNvmCalDataChannel`** | `ROS2 -> AIS SCS` | `LpsSaNvmCalDataChannelOutput` | `lps_sa_nvm_cal_data_channel` | `weigh_app_interfaces::msg::LpsSaNvmCalDataChannel` | Forwards NVM calibration parameters (lift/tilt pressure curves, speeds, IMU cal results) from ROS2 WeighApp to SCS. |
| **`LpsSaNvmCalOnTheFlyDataChannel`** | `ROS2 -> AIS SCS` | `LpsSaNvmCalOnTheFlyDataChannelOutput` | `lps_sa_nvm_cal_on_the_fly_data_channel` | `weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel` | Forwards on-the-fly dynamic calibration calculation metrics to SCS. |
| **`CalMgrCmdReqst`** | `AIS SCS -> ROS2` | `CalMgrCmdReqstInput` | `cal_mgr_cmd_reqst` | `weigh_app_interfaces::msg::CalMgrCmdReqst` | Forwards calibration manager requests (Empty/Full bucket calibration commands, calibration iterm bits) from SCS ACD to ROS2 WeighApp. |
| **`CalMgrCmdResp`** | `ROS2 -> AIS SCS` | `CalMgrCmdRespOutput` | `cal_mgr_cmd_resp` | `weigh_app_interfaces::msg::CalMgrCmdResp` | Relays calibration execution status and response codes from ROS2 WeighApp back to SCS ACD. |
| **`DemoAppTxChannel`** | `AIS SCS -> ROS2` | `DemoAppTxChannelInput` | `demo_app_tx_channel` | `weigh_app_interfaces::msg::DemoAppTxChannel` | Forwards simulation and demo sensor playback signals from SCS to ROS2 nodes. |
| **`PartNumbers`** | `AIS SCS -> ROS2` | `PartNumbersInput` | `part_numbers` | `weigh_app_interfaces::msg::PartNumbers` | Forwards ECM hardware and software part number telemetry from SCS to ROS2 nodes. |
| **`SystemHardwareHealth`** | `AIS SCS -> ROS2` | `SystemHardwareHealthInput` | `system_hardware_health` | `weigh_app_interfaces::msg::SystemHardwareHealthStorage` | Forwards system hardware sensor health status indicators to ROS2. |
| **`SystemHardwareHealthRequest`** | `ROS2 -> AIS SCS` | `SystemHardwareHealthRequestOutput` | `system_hardware_health_request` | `weigh_app_interfaces::msg::SystemHardwareHealthRequest` | Forwards diagnostic polling queries from ROS2 nodes to SCS hardware monitors. |
| **`ReadyToFlashStatus`** | `ROS2 -> AIS SCS` | `ReadyToFlashStatusOutput` | `ready_to_flash_status` | `weigh_app_interfaces::msg::ReadyToFlashStatus` | Relays calibration flash readiness state from ROS2 WeighApp to SCS flash controllers. |

---

## Architectural Principles

1. **One-Way Bridging Per Channel**: Avoids cyclic dependency loops and ensures clear message ownership across the boundary.
2. **Deterministic Rate Handling**: The bridge execution cycle (`executive()`) drains all pending queues on each cycle using `while(channel->get(...))` loops.
3. **Pure Conversion Functions**: Data conversion logic is implemented in static helper methods without side effects or hidden global state.

## Files & Configuration

| File | Purpose |
|---|---|
| `ScsToRos2Bridge.h` | Class declaration: SCS interface pointers, ROS2 node/executor, ROS2 wrapper members, static conversion helpers. |
| `ScsToRos2Bridge.cpp` | `initialize()` (bind AIS SCS + set up ROS2), `executive()` (drain-and-forward loop, called at `cycleRate_hz`), `cleanup()`, and field-by-field conversion functions. |
| `SConscript` | SCons build recipe linking against `ros2_jazzy_sdk`, `ros2_models`, and `CPM-Loader-ais/prod/common/ros2wrapper`. Includes `#` and `myEnv['SSP_DIR']` paths for required SCS definitions (`lps_cal`, `lps_weighing`, `lps_common`, etc.). |
| `../../config/ScsToRos2Bridge.rb` | Ruby task configuration file defining task interface registrations and execution parameters. |


