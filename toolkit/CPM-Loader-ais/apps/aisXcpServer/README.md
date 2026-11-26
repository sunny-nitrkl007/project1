# aisXcpServer (XcpServerTask)

## Overview

XCP measurement server for the calibration tool. Two XCP-on-UDP servers (ports 60000 and 60001, one 10 ms DAQ event)
serve a measurement database that `XcpScsInputs::update()` fills from the app's inputs. The app also writes the
tip-off-assist CSV log `/opt/appdata/CPM/debug/toa_log.csv`.

Migrated from an AIS `task::Task` to a ROS2 node (`ros2_wrapper::Ros2TaskWrapper`), with the migrated LpsSaWeighApp as
the reference pattern. The XCP protocol, the A2L file (`CPM_A6N2_XCP.a2l`), `xcp_server/` and the measurement logic
are unchanged; file names are kept.

**The app is completely independent of AIS** (decision 2026-11-24). It includes, compiles and links nothing from
AIS: no `eta-ais` or `TES-common-ais` header or source, no `ais_*` / `hub_*` library, no `AIS_*` CMake variable, no
legacy SCS channel type, no `AIS_LOG_*`. Every input is the ROS2 message its producer publishes. Every AIS ↔ ROS2
conversion lives in `ScsToRos2Bridge`, which carries the producers that are still AIS apps.

**Why WeighApp, JobMgr and other apps' data appear here:** aisXcpServer has no data of its own. It shows other apps'
live data (WeighApp, JobMgr, Tipoff, PWM, health, ...) to the XCP tool. The original AIS app already read these
channels; the migration only changes how the data arrives (a ROS2 subscription instead of an SCS channel).

## XCP measurement contract (unchanged)

The A2L file addresses measurements by `(group << 16) | offset`; the C++ type of each value pushed with
`db.update()` fixes the measurement size (`xcp_server/db/XCPServerDb.hpp` has one overload per type). Therefore:

- `update()` reads the ROS2 message fields directly, and each read keeps the **legacy C++ type**: where the ROS2 field
  type differs, the read is `static_cast<legacy type>(msg.field)` (same value conversion as before, same size).
  The 595 `db.update` / `DB_PUSH` calls keep their order, addresses and array lengths (checked against the AIS
  version).
- Legacy enum constants are replaced by the ROS2 message constants (`WeighReqstChannelCommand`,
  `JobMgrReqstChannelCommand`, `LpsSaJobMgrReqst`, `DataLinkParam`), all values checked equal to the legacy enums.
  Legacy getters are replaced by the field they return (e.g. `LpsSaJobMgrReqst::truckTargetWeight()` → `arg2`,
  `GetLastGoodValueVector()` / `GetVarParamBlock()` → `var_param_block`).
- Two legacy constants are local values (`LPS_WEIGH_OVERLOAD_LEVEL_NONE` = 0, `DSI_CODE_OK()` = 0); the platform
  macros `OEL_UNPACK_LE_8/24` are replaced by local little-endian unpack macros that advance the pointer the same
  way (`XCP_UNPACK_LE_8/24`; assumption: the SDK `lib_oel` header is not in the source snapshot).
- `RosInData<Msg>` (the ROS2 message is the base class) reproduces the SCS input: at most the AIS `queueSize`
  messages are kept (oldest dropped), `update()` takes one message per cycle, and the rx timeouts (`isTimedOut()`)
  are kept; as in AIS, nothing calls them.

## Channels (23 former SCS inputs)

| # | Former SCS input | ROS2 topic | ROS2 message | Publisher | AIS queueSize |
|---|---|---|---|---|---:|
| 1 | SystemHardwareHealthInput | `system_hardware_health` | `weigh_app_interfaces/SystemHardwareHealthStorage` | bridge (AIS platform) | 100 |
| 2 | LpsSaWeighReqstChannelInput | `lps_sa_weigh_reqst_channel` | `cpm_common_interfaces/LpsSaWeighReqstChannel` | JobMgr + bridge (AIS apps) | 20 |
| 3 | LpsSaWeighRespChannelInput | `lps_sa_weigh_resp_channel` | `cpm_common_interfaces/LpsSaWeighRespChannel` | WeighApp | 20 |
| 4 | LpsSaWeighTxChannelInput | `lps_sa_weigh_tx_channel` | `cpm_common_interfaces/LpsSaWeighTxChannel` | WeighApp | 20 |
| 5 | LpsSaWeighDebugChannelInput | `lps_sa_weigh_debug_channel` | `weigh_app_interfaces/LpsSaWeighDebugChannel` | WeighApp | 1 |
| 6 | LpsSaWeighInitDebugChannelInput | `lps_sa_weigh_init_debug_channel` | `weigh_app_interfaces/LpsSaWeighInitDebugChannel` | WeighApp | 1 |
| 7 | LpsSaNvmCalDataChannelInput | `lps_sa_nvm_cal_data_channel` | `weigh_app_interfaces/LpsSaNvmCalDataChannel` | WeighApp (once at startup, transient-local) | 1 |
| 8 | LpsSaNvmCalOnTheFlyDataChannelInput | `lps_sa_nvm_cal_on_the_fly_data_channel` | `weigh_app_interfaces/LpsSaNvmCalOnTheFlyDataChannel` | WeighApp | 3 |
| 9 | LpsSaJobMgrTxChannelInput | `lps_sa_job_mgr_tx_channel` | `job_mgr_interfaces/LpsSaJobMgrTxChannel` | JobMgr | 20 |
| 10 | PwmInputChannelsInput | `pwm_input_channels` | `weigh_app_interfaces/PwmInputChannels` (4 fields appended) | bridge (PwmInput) — new leg | 30 |
| 11 | LpsSaJobMgrReqstChannelInput | `lps_sa_job_mgr_reqst_channel` | `cpm_common_interfaces/LpsSaJobMgrReqstChannel` | WeighApp + bridge (AIS apps) | 20 |
| 12 | LpsSaJobMgrRespChannelInput | `lps_sa_job_mgr_resp_channel` | `job_mgr_interfaces/LpsSaJobMgrRespChannel` | JobMgr | 20 |
| 13 | LpsSaJobMgrDebugChannelInput | `lps_sa_job_mgr_debug_channel` | `job_mgr_interfaces/LpsSaJobMgrDebugChannel` | JobMgr | 1 |
| 14 | SwitchInputScsInput | `switch_input_scs` | `job_mgr_interfaces/SwitchInputScs` | bridge (SwitchInput) | 1 |
| 15 | CycleSegTxChannelInput | `cycle_seg_tx_channel` | `cpm_common_interfaces/CycleSegTxChannel` (new) | bridge (CycleSeg) — new leg | 1 |
| 16 | WorkOrderAssistTxInput | `work_order_assist_tx_channel` | `cpm_common_interfaces/WorkOrderAssistTxChannel` (new) | bridge (WorkOrderAssist) — new leg | 5 |
| 17 | TipoffModelTestPointsInput | `tipoff_model_test_points` | `weigh_app_interfaces/TipoffModelTestPoints` | WeighApp | 20 |
| 18 | AutonomyConditionDiagnosticsTxInput | `autonomy_condition_diagnostics_tx_channel` | `cpm_common_interfaces/AutonomyConditionDiagnosticsTxChannel` | bridge (AutonomyConditionDiagnostics) | 5 |
| 19 | BEMSimStateInput | `lps_sa_ui_bem_sim_state_interface` | `cpm_common_interfaces/LpsSaUIBemSimStateInterface` (new) | bridge (AisJhm2DataServer) — new leg | 1 |
| 20 | WidgetsDebugDataInput | `widgets_debug_data` | `cpm_common_interfaces/WidgetsDebugData` (new) | bridge (WidgetApp) — new leg | 20 |
| 21 | DataLinkDataInput | `weigh_app_data_link_data` | `weigh_app_interfaces/DataLinkData` | bridge (datalink producers) | 30 |
| 22 | DisplayStateInput | `lps_sa_ui_display_state_interface` | `cpm_common_interfaces/LpsSaUIDisplayStateInterface` | bridge (AIS UI; existing leg, also read by WeighApp/JobMgr) | 1 |
| 23 | MachineInput | — | — | none | 1 |

22 subscriptions. 21 use the wrapper's default QoS (reliable, volatile, keep-last) with history depth
`max(10, queueSize)`; `lps_sa_nvm_cal_data_channel` uses `rclcpp::QoS(1).transient_local()`, matching the WeighApp
publisher.

**Not migrated:** **MachineInput** — no task publishes the `Machine` channel and `m_machine` is never read. The member
is kept with its defaults; there is no topic to subscribe to.

### Known differences

- **Before the first message of a topic**, XCP shows the ROS2 defaults (0 / false) of that channel. In AIS it showed
  the legacy constructor defaults, which are non-zero for about 20 status fields (e.g. `LPS_STATUS_BAD`,
  `..._UNKNOWN`, `activeJobId = -1`). From the first message on, the values are the same. Not changed (it would
  need the legacy enum values in the app); can be added as a local default table if required.
- **DisplayState is now migrated.** The old version could not rebuild the legacy `LpsSaUIDisplayState` object;
  reading the ROS2 fields (`heartbeat_count`, `service_mode_enable_code_entered`, `in_service_mode`,
  `document_id`) removes that blocker.
- **PWM `period` / `width`** are unbounded arrays in the message; a missing element reads 0 (the legacy arrays were
  fixed-size and value-initialised to 0).
- **DEBUG log of received data** prints the message with the generated ROS2 `to_yaml()` instead of the legacy CSV
  (`csvable`). Only at `debug` level.
- **Request topics** carry the requests of the ROS2 apps and of the bridged AIS apps — the same set of writers as the
  original all-AIS SCS channels.
- **BEMSim `newMachine`** is not used (it was never serialized over SCS); XCP does not read it.
- **Startup:** the former `ScsRxTimeouts` section can no longer be missing (parameter defaults), so the old
  "Couldn't find ScsRxTimeouts" exit path is gone. As in AIS, the results of `initReadInterface()` and
  `xcpServerDbInit()` are not checked by `initialize()` (legacy; kept as is by decision of 2026-11-23).
- **Logging:** AIS NOTICE → `RCLCPP_INFO`, FATAL → `RCLCPP_ERROR`. `TipoffAssistLogging.hpp` logs the file path with
  `RCLCPP_ERROR_STREAM`: the original `AIS_LOG_ERROR("%s", filePath_)` passed a `std::string` to a printf-style call
  (undefined behaviour) — reported to the customer. `xcpServerDbUpdate()` still logs INFO every cycle (legacy).
  The TOA log start time uses a local copy of `tes_common_ais::putTime()` (same `gmtime_r` + `strftime`, `%FT%T`).

### Decisions and status

| Item | Solution | Status |
|---|---|---|
| **AIS independence** | `update()` and `executive()` read ROS2 fields with the legacy C++ types; no app-side converter; no AIS header, source or library | **Implemented** 2026-11-24 |
| **DisplayStateInput** | Subscribed to the existing bridge topic; fields read directly | **Implemented** 2026-11-24 |
| **PWM group, offsets 0–3** | Four fields appended to `weigh_app_interfaces/PwmInputChannels.msg`; the bridge fills them | **Implemented** (needs regenerated `weigh_app_interfaces`) |
| **NVM calibration snapshot** | Optional `rclcpp::QoS` constructor in `RosOutputInterface.h` / `RosInputInterface.h`; `rclcpp::QoS(1).transient_local()` on the WeighApp publisher and the aisXcpServer subscriber | **Implemented** |
| **MachineInput** | Nothing to migrate | Final |
| **Startup: XCP init results unchecked** | Kept as is (legacy); reported to the customer | **Kept by decision** |
| **Defaults before the first message** | ROS2 defaults instead of legacy constructor defaults | Open (accept, or add a default table) |

## Files changed by the migration

**In this app (`apps/aisXcpServer/`)**

| File | Change |
|---|---|
| `XcpServerTask.h` / `.cpp` | `Ros2TaskWrapper` node, `main()`, parameters, 22 subscriptions, cleanup; `executive()` passes the ROS2 fields to `toaLogging.update()` |
| `XcpScsInputsDb.h` | `RosInData<Msg>` replaces `SCSInData<T>`; `update()` reads ROS2 fields (same addresses, order and C++ types); `RosInputs`, `initReadInterface`, `stop` |
| `xcpServerDb.cpp` | logging calls only (AIS log → rclcpp) |
| `TipoffAssistLogging.hpp` | logging calls; local `putTimeUtc()` instead of `TES-common-ais` `chrono/print.hpp`; the 3 `TipAssist*Status_t` constants it compares against are local copies (values from `tipoff_assist/.../toa_wl00_types.h`, whose `std_t.h` comes from `eta-ais`); standard includes made explicit |
| `CMakeLists.txt`, `README.md` | new |
| `SConscript` | **deleted** |

**Outside this app**

| File | Change | Why |
|---|---|---|
| `ros2_config/XcpServerTask.yaml` | new | parameters (replaces `config/XcpServerTask.rb`) |
| `config/XcpServerTask.rb` | **deleted** | replaced by the YAML |
| `config/xcp_server_task.monitrc`, `config/monitrc` | new / include added | Monit supervision |
| `config/CommonTasks.rb`, `config/ExecutionTable_CPM.rb` | app entries removed | no longer an AIS task |
| `config/ScsToRos2Bridge.rb` | 5 keys | new bridge legs |
| `apps/CMakeLists.txt`, `apps/SConscript` | add_subdirectory / buildit line removed | build |
| `scripts/monit_start.sh`, `monit_stop.sh`, `StopPrograms.sh` | start first, stop last, listed | launch |
| `ssp-CPM_Loader-ais/Makefile` | YAML copy, monitrc install | deploy |
| `apps/ScsToRos2Bridge/*` (`.h`, `.cpp`, `CMakeLists.txt`, `SConscript`, `README.md`) | 5 SCS→ROS2 legs (Pwm, WorkOrderAssist, CycleSeg, Widgets, BEMSim) | AIS producers that are not ROS2 apps yet; all AIS ↔ ROS2 conversion |
| `prod/common/ros2wrapper/RosInputInterface.h`, `RosOutputInterface.h` | optional `rclcpp::QoS` constructor (approved) | NVM snapshot |
| `apps/LpsSaWeighApp/LpsSaWeighApp.cpp` | NVM publisher `QoS(1).transient_local()` — one line | NVM snapshot. If WeighApp must stay untouched, revert this line **and** the aisXcpServer NVM subscription QoS together |
| `ROS2_MSG/.../cpm_common_interfaces/msg/*` (9 new) + `CMakeLists.txt` | new messages | inputs with no ROS2 message before |
| `ROS2_MSG/.../weigh_app_interfaces/msg/PwmInputChannels.msg` | 4 fields appended (approved) | PWM group offsets 0–3 |
| `ws4-mw-CPM_Porting_Integration/README.md` | route tables | bridge routes |

## Configuration

`ros2_config/XcpServerTask.yaml` (root `XcpServerTask:` = `--instance` name):

| Parameter | Value | Former source |
|---|---|---|
| `cycle_rate_hz` | `100.0` | `XcpServerTask.rb` `"cycleRate_hz" => 100` (must match the 10 ms XCP event) |
| `logger_threshold` | `"error"` | `XcpServerTask.rb` `"loggerThreshold" => "error"` |
| `scheduler` | `"SCHED_OTHER"` | `commonTaskParams.rb` (A7H4 is not an AUTO ECM) |
| `scheduler_priority` | `0` | no priority for `SCHED_OTHER` |
| `scs_rx_timeouts.<input>_rx_timeout_sec` (21 keys) | 5.0 / 10.0 | `XcpServerTask.rb` `ScsRxTimeouts` (all except `MachineInput`) |

No per-machine keys (no Robot YAML).

## Build and launch

- **Build prerequisite:** regenerate (colcon, `aarch64.cmake`) from `ROS2_MSG/ROS2_MSG/src` and copy into
  `ros2_models` before this app, the bridge and WeighApp compile: the 9 new `cpm_common_interfaces` messages
  (`WorkOrderAssistTxChannel`, `CycleSegTxChannel`, `CycleSegInputs`, `CycleSegOutputs`, `LpsSaUIBemSimStateInterface`,
  `BemSimCnfg`, `WidgetsDebugData`, `WidgetsTireRevDistances`, `WidgetsTireRevRotations`) and the extended
  `weigh_app_interfaces/PwmInputChannels`.
- **Build:** `apps/aisXcpServer/CMakeLists.txt` (`add_subdirectory(aisXcpServer)` in `apps/CMakeLists.txt`); the former
  `SConscript` is deleted. Sources: `xcp_server/`, `XcpServerTask.cpp`, `xcpServerDb.cpp`. Include roots: ROS2 SDK,
  `ros2_models`, the app, `prod/common` (`ros2wrapper`, `ROS2Logger.hpp`). Links: ROS2, the three message packages,
  Boost `filesystem`/`system`, system libraries. The only AIS-named paths are build locations behind variables:
  `XCP_IMAGE_DIR` (image staging directory the Makefile deploys every app from, `eta-ais/build-A7H4-adv`) and
  `XCP_TARGET_SYSROOT` (toolchain sysroot).
- **Launch:** `scripts/monit_start.sh` starts it first (`--instance XcpServerTask`, pidfile `/run/xcp_server_task.pid`,
  only `XcpServerTask.yaml`), then `sleep 2`; `scripts/monit_stop.sh` stops it last; supervised by
  `config/xcp_server_task.monitrc` (included from `config/monitrc`); listed in `scripts/StopPrograms.sh`. Removed from
  `config/CommonTasks.rb` and `config/ExecutionTable_CPM.rb`; `config/XcpServerTask.rb` is deleted.
- **Deploy:** `ssp-CPM_Loader-ais/Makefile` copies `XcpServerTask.yaml` and installs `xcp_server_task.monitrc`.
- `ScsToRos2Bridge` must run (it carries the AIS producers of 12 inputs, including DisplayState).
- The older `ReadMe` in this folder describes the former SCons build.
- Not compiled here (no toolchain in this environment): the first build must confirm the ROS2 distribution provides
  the generated `to_yaml()` (ROS2 Humble or later) and that `ldd aisXcpServer` lists no AIS library.
