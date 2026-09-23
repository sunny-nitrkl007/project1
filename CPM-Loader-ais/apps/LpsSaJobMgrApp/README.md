# LpsSaJobMgrApp - Channel-Wise Architecture & ROS2 Migration Summary

## Overview

`LpsSaJobMgrApp` is the core job and task management application for the Loader Payload System (LPS). It manages truck loading passes, tare/payload calculations, load records, tickets, simple calibration, and machine/operator workflows.

This application has been migrated from legacy **AIS SCS (Shared Memory Communication Service)** to **ROS2 / DDS** communication using `ros2wrapper` (`RosInputInterface` and `RosOutputInterface`).

---

## Summary of Channel-Wise Changes

Below is the exhaustive list of all communication channels used by `LpsSaJobMgrApp`, detailing previous AIS SCS implementations versus the updated ROS2 interfaces.

| Channel Name | Direction | Old Implementation (AIS SCS) | New Implementation (ROS2) | Topic / Message Type | Summary of Changes |
|---|---|---|---|---|---|
| **`LpsSaJobMgrTxChannel`** | Output | `LpsSaJobMgrTxChannelOutput* LpsSaJobMgrScsTxOut` (via `InterfaceDb::fetch`) | `RosOutputInterface<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>* LpsSaJobMgrTxRosOut_` | `lps_sa_job_mgr_tx_channel`<br>`job_mgr_interfaces::msg::LpsSaJobMgrTxChannel` | Migrated Job Manager telemetry to ROS2. Implemented `convertJobMgrTxToRos()` to map weights, truck/material IDs, target configurations, calibration parameters, and operational modes into ROS2 messages. |
| **`LpsSaJobMgrReqstChannel`** | Input | `LpsSaJobMgrReqstChannelInput*` (via `InterfaceDb::bind`) | `RosInputInterface<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>* LpsSaJobMgrReqstIn` | `lps_sa_job_mgr_reqst_channel`<br>`cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel` | Subscribes to incoming commands and workflow requests (target weights, truck resets, ticket changes, zeroing) over ROS2. |
| **`LpsSaJobMgrRespChannel`** | Output | `LpsSaJobMgrRespChannelOutput*` (via `InterfaceDb::fetch`) | `RosOutputInterface<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>* LpsSaJobMgrRespChannelOutput_` | `lps_sa_job_mgr_resp_channel`<br>`job_mgr_interfaces::msg::LpsSaJobMgrRespChannel` | Transmits request acknowledgements, return codes, and error statuses for requested commands via ROS2. |
| **`LpsSaJobMgrDebugChannel`** | Output | `LpsSaJobMgrDebugChannelOutput* LpsSaJobMgrScsDebugOut` (via `InterfaceDb::fetch`) | `RosOutputInterface<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>* LpsSaJobMgrDebugRosOut_` | `lps_sa_job_mgr_debug_channel`<br>`job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel` | Publishes internal debug metrics, pass tracker state machine status, and Tip-Off Assist activation counts. |
| **`SwitchInputScs`** | Input | `SwitchInputScsInput* LpsSaSwitchInput` (via `InterfaceDb::fetch`) | `RosInputInterface<job_mgr_interfaces::msg::SwitchInputScs>* LpsSaSwitchInput` | `switch_input_scs`<br>`job_mgr_interfaces::msg::SwitchInputScs` | Migrated physical switch inputs to ROS2. Updated store button detection to check `stg_values[3].value == STG::CLOSED` (STG4). |
| **`OutputChannel`** | Output | `OutputChannelOutput* LpsSaOutputChannelOut` (via `InterfaceDb::fetch`) | `RosOutputInterface<job_mgr_interfaces::msg::OutputChannel>* LpsSaOutputChannelRosOut_` | `output_channel`<br>`job_mgr_interfaces::msg::OutputChannel` | Migrated horn on store and discrete output activations to ROS2 message commands (`OutputCmd`). |
| **`AisJhm2TxChannel`** | Input | `AisJhm2TxChannelInput*` (via `InterfaceDb::bind`) | `RosInputInterface<cpm_common_interfaces::msg::AisJhm2TxChannel>* AisJhm2TxInput` | `ais_jhm2_tx_channel`<br>`cpm_common_interfaces::msg::AisJhm2TxChannel` | Receives Job Handler Module 2 dispatch updates to reset and clear simple calibration cache (`simpleCal_.eraseAll()`). |
| **`LpsSaUIDisplayStateInterface`** | Input | `LpsSaUIDisplayStateInterfaceInputChannel* displayStateInput_` (via `InterfaceDb::bind`) | `RosInputInterface<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface>* displayStateInputRos_` | `lps_sa_ui_display_state_interface`<br>`cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface` | Reads display state and verification mode flags (`in_verification_mode`) to place Job Manager in Standby mode during verification. |
| **`ShmClockInput`** | Input | `ShmClockInput* ShmClockInputScs` (via `InterfaceDb::fetch`) | `RosInputInterface<cpm_common_interfaces::msg::ShmClockInput>* ShmClockInputRos` | `shm_clock_input`<br>`cpm_common_interfaces::msg::ShmClockInput` | Reads Service Hour Meter (SHM), UTC offset, and timezone info over ROS2 to update local clocks and load record timestamps. |
| **`DataLinkData`** | Input | `DataLinkDataInput* dataLinkDataInput_` (via `InterfaceDb::bind`) | `RosInputInterface<job_mgr_interfaces::msg::DataLinkData>* dataLinkDataInputRos_` | `data_link_data`<br>`job_mgr_interfaces::msg::DataLinkData` | Ingests CAN/J1939 datalink PIDs for store button triggers (`0xD1182A`), tipoff assist (`0xD118CE`), and manual add (`0xD11890`). |
| **`LpsSaLoadRecordChannel`** | Output | `LpsSaLoadRecordChannelOutputChannel* loadRecordOutputChannel_` (via `InterfaceDb::fetch`) | `RosOutputInterface<job_mgr_interfaces::msg::LpsSaLoadRecordChannel>* loadRecordOutputChannel_` | `lps_sa_load_record_channel`<br>`job_mgr_interfaces::msg::LpsSaLoadRecordChannel` | Publishes finalized load records upon store. Implemented `convertLoadRecordToRos()` to serialize full load records, including subtotals, passes, timestamps, and weights. |
| **`AutonomyConditionDiagnosticsTxChannel`** | Input | `AutonomyConditionDiagnosticsTxInterfaceInputChannel* autonomyConditionDiagnosticsTxInputChannel_` (via `InterfaceDb::fetch`) | `RosInputInterface<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>* autonomyConditionDiagnosticsTxInputRos_` | `autonomy_condition_diagnostics_tx_channel`<br>`cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel` | Inspects Software Enabled Attachment (SEA) feature licenses for Level 1 Essentials (149), Level 2 Pro (245), and Legal-For-Trade (312). |
| **`EventDiagnosticData`** | Input | `EventDiagnosticDataInput* eddtInputChannel_` (via `InterfaceDb::bind`) | `RosInputInterface<job_mgr_interfaces::msg::EventDiagnosticData>* eddtInputRos_` | `event_diagnostic_data`<br>`job_mgr_interfaces::msg::EventDiagnosticData` | Monitors diagnostic fault codes and event IDs to identify memory-full conditions and track active Tip-Off Assist EIDs. |
| **`LpsSaWeighReqstChannel`** | Output | Dual-publishing via `LpsSaWeighScsReqstOut` and `DDSWeighAppInf` | Dedicated ROS2 interface via `DDSWeighAppInf` | `lps_sa_weigh_reqst_channel`<br>`cpm_common_interfaces::msg::LpsSaWeighReqstChannel` | Removed obsolete raw SCS dual-publish fallback; all requests to WeighApp are routed exclusively over DDS/ROS2. |

---

## Build System (`SConscript`) Changes

- Updated `CPPPATH` discovery for ROS2 wrappers to cleanly reference `CPM-Loader-ais/prod/common/ros2wrapper`.
- Configured compilation against `ros2_jazzy_sdk` and `ros2_models` libraries.
