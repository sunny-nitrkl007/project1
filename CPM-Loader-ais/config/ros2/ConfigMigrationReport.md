# Config Migration Report — LpsSaJobMgrApp & LpsSaWeighApp

**Scope**: Migration of AIS Ruby task configuration (`config/LpsSaJobMgrApp.rb`,
`config/LpsSaWeighApp.rb`) to native ROS2 parameters (YAML files in this directory),
for the two already-ROS2-migrated apps `LpsSaJobMgrApp` and `LpsSaWeighApp`.

**Status as of this report**: Phases 1–3 (inventory, YAML authoring, guarded code
changes) implemented. Phase 4 (build + side-by-side runtime verification) and
Phase 5 (cutover) **not yet done** — see `config_migration_plan.md` at
`/home/rushabhm/cpm_migration/cpm_ai/config_migration_plan.md` for the full phased
plan this report is derived from.

**How this works today, in one line**: both apps still read every value from the old
`.rb` file exactly as before; a new guarded ROS2-parameter read sits next to each
migrated value and only overrides it if a YAML file is actually deployed at
`$CAT_CONFIG_DIR/ros2/<file>.yaml`. Nothing is deleted. Nothing changes in behavior
until a YAML file is placed there.

---

## 1. What Has Been Migrated

| Config Key | App | Old Source (`.rb`) | New Source (YAML) | Code Location of Guarded Override |
|---|---|---|---|---|
| `storageRoot` | LpsSaJobMgrApp | `config/LpsSaJobMgrApp.rb` | `lps_sa_job_mgr_app_params.yaml` → `storage_root` | `LpsSaJobMgrApp.cpp` `initialize()`, right after the `.rb` read |
| `SimpleCalMaxTrucksSupported` | LpsSaJobMgrApp | `config/LpsSaJobMgrApp.rb` | `lps_sa_job_mgr_app_params.yaml` → `simple_cal_max_trucks_supported` | `LpsSaJobMgrApp.cpp` `initialize()`, "Simple Cal Max Trucks" block |
| `cycleRate_hz` | LpsSaWeighApp | `config/LpsSaWeighApp.rb` | `lps_sa_weigh_app_params.yaml` → `cycle_rate_hz` | `LpsSaWeighApp.cpp` `initialize()`, "Weighing App execution rate" block |
| `tempRoot` | LpsSaWeighApp | `config/LpsSaWeighApp.rb` | `lps_sa_weigh_app_params.yaml` → `temp_root` | `LpsSaWeighApp.cpp` `initialize()`, "Set up storage root" block |
| `storageRoot` | LpsSaWeighApp | `config/LpsSaWeighApp.rb` | `lps_sa_weigh_app_params.yaml` → `storage_root` | `LpsSaWeighApp.cpp` `initialize()`, "Set up storage root" block |
| `CPMExecTxPeriod` | LpsSaWeighApp | `config/LpsSaWeighApp.rb` | `lps_sa_weigh_app_params.yaml` → `cpm_exec_tx_period` | `LpsSaWeighApp.cpp` `initialize()`, "Get App Tx Period" block |
| `CPMExecRate` | LpsSaWeighApp | `config/LpsSaWeighApp.rb` | `lps_sa_weigh_app_params.yaml` → `cpm_exec_rate` | `LpsSaCalibration.cpp` `LpsSaInitWeighTbl()` |

**Why these and not others**: these are exactly the keys for which a concrete,
verifiable `getTaskConfig().get(...)` call site was found in the app's own `.cpp`
source. Every other key in each `.rb` file was checked and either has no reading
call site in-repo, or is consumed by AIS infrastructure the app doesn't own (see
Section 2).

---

## 2. What Has NOT Been Migrated, and Why

| Config Key | App | Reason Not Migrated | When It CAN Be Migrated |
|---|---|---|---|
| `scheduler` | Both | Sets the Linux OS thread scheduling policy (`SCHED_RR`) via `sched_setscheduler()`, called inside AIS `task::Task`/`TaskCore.cpp:1037`. This is an OS-level setting, not app configuration data — there is no ROS2 parameter concept that maps to "set my thread's OS scheduler." | Only when `task::Task` itself is replaced by a native `rclcpp` entry point (no longer inheriting from AIS `Task`). At that point, RT scheduling is set explicitly via `sched_setscheduler`/`chrt` in the new entry point. This is a separate, later effort — full AIS-framework decoupling, not a config-only change. |
| `schedulerPriority` | Both | Same reason as `scheduler` — the numeric priority passed to the same `sched_setscheduler()` call. | Same trigger as `scheduler` above. |
| `cycleRate_hz` | LpsSaJobMgrApp only | For this app, this key is read **only** by the AIS `task::Task` base class itself (`BasicTask<_Policy>::parseExecutiveConfiguration()`, `ais_task/ais/task/Task.cpp:244`), where it sets the period of the `CycleBasedExecutive` thread that calls `LpsSaJobMgrApp::executive()`. Verified: no `getTaskConfig().get("cycleRate_hz", ...)` call exists anywhere in `LpsSaJobMgrApp.cpp`/`.h` itself. (Contrast with `LpsSaWeighApp`, which *is* migrated — it separately reads this same key into its own `LpsSaWeighInfoTbl.CycleRate_hz` for business-logic use, which is a distinct, app-owned read.) | Same trigger as `scheduler`/`schedulerPriority` — only when `task::Task`'s executive-loop mechanism is replaced by a ROS2-native timer (e.g. `rclcpp::WallTimer`) driving the equivalent of `executive()` directly. |
| `loggerThreshold` | Both | Configures the AIS logger's verbosity threshold for `getLogger()`/`AIS_LOG_*` calls — an AIS-logging-infrastructure setting, not a value the app's business logic reads or acts on. | Independently, at any time — not gated on anything else in this migration. Requires swapping `AIS_LOG_*`/`getLogger()` calls for `RCLCPP_INFO/WARN/ERROR` etc., then verbosity becomes controllable via `--ros-args --log-level`. Can be done as its own bounded, mechanical task. |
| `ChassisIMU.*` (11 IMU filter/bias tuning floats) | LpsSaWeighApp | Read inside `LpsSaChassisIMU::init(const TaskParser& taskParser)` (`LpsSaChassisIMU.h:84-172`). Migrating requires changing that function's signature — it currently takes an AIS `TaskParser&`, not a ROS2 node or parameter source. No compiler/build environment was available in this environment to compile-verify a signature change to a sensor-fusion configuration path, so it was left untouched rather than risk an unverified change. | As soon as a build environment is available to compile-test the signature change (pass the ROS2 node, or the already-resolved values, into `LpsSaChassisIMU::init()` instead of a `TaskParser&`). Mechanically similar to the changes already made elsewhere; the only blocker was the inability to compile-verify here. |
| `ConditionConfig.AutonomyConditions` (15-entry condition name list) | LpsSaWeighApp | No call site reading this key was found anywhere in `LpsSaWeighApp`'s own `.cpp`/`.h` source, despite a repo-wide search. It may be consumed by a different AIS subsystem/library at a level not visible in this repo, or it may be unused/stale. | Needs confirmation from the original author on whether/where this key is actually consumed before any migration attempt — migrating a key nobody reads risks masking a real gap, and dropping it without confirmation risks breaking something outside this repo's visibility. |
| `ScsRxTimeouts.SystemHardwareHealthRequestOutput_txRate_sec` | LpsSaWeighApp | Same as above — no reading call site found in-repo despite the key being declared in the `.rb` file. | Same as above — confirm with original author first. |

---

## 3. Before vs. After — Behavior Comparison Table

| Aspect | Previously (AIS / Ruby) | Now (Current State, Post-Migration-So-Far) |
|---|---|---|
| **Config file format** | Ruby hash literals (`config/LpsSaJobMgrApp.rb`, `config/LpsSaWeighApp.rb`) | YAML files (`lps_sa_job_mgr_app_params.yaml`, `lps_sa_weigh_app_params.yaml`) — additive, not a replacement yet |
| **How the app finds its config** | AIS `task::Task` looks up `$CAT_CONFIG_DIR/<TaskName>.rb` automatically by task name at startup | App explicitly checks for `$CAT_CONFIG_DIR/ros2/<yamlFileName>.yaml` via a new helper function (`buildRosNodeOptionsWithParamsFile()`); if absent, silently falls back to old behavior |
| **Read mechanism in code** | `getTaskConfig().get("key", variable)` — AIS `ConfigSection` API | `rosNode_->declare_parameter("key", defaultFromRbValue)` then `rosNode_->get_parameter("key")` — ROS2 `rclcpp::Node` parameter API |
| **Precedence when both exist** | N/A (only one source existed) | `.rb` value is read first and used as the ROS2 parameter's *default*; YAML value (if present) overrides it. If no YAML file is deployed, the `.rb` value is what's actually used — behaviorally identical to before |
| **`rosNode_` construction timing** | N/A — ROS2 node was constructed partway through `initialize()`, after config values were already consumed | Moved to the top of `initialize()` in both apps, *before* any of the migrated config values are read, so parameter overrides are available in time. Verified nothing between the old and new construction points depended on `rosNode_` existing |
| **Launch/CLI mechanism** | N/A | Deliberately NOT using `ros2 launch --params-file`, because `getTaskImplementation()` in both apps calls `rclcpp::init(0, nullptr)`, which discards argc/argv — a launch file's `--params-file` argument would never reach the node. Self-contained file-existence check used instead |
| **Process launch / scheduling** | AIS `ApplicationTable.rb` / `ExecutionTable_CPM.rb` / `AlwaysOnTasks.rb`; AIS `task::Task` executive loop; `sched_setscheduler(SCHED_RR, priority)` | **Unchanged.** Still fully AIS-driven; not touched by this migration at all |
| **NVM / calibration persistence** | Boost-serialized `.bin` files under `storageRoot`/`tempRoot` (paths themselves are migrated; the serialization mechanism is not) | **Unchanged.** Only the *path values* are migratable; the persistence format and mechanism stay as-is — explicitly out of scope (see `config_migration_plan.md` non-goals) |
| **Peer apps still on legacy SCS** (e.g. `LpsSaTotalsApp`, `WorkOrderAssist`, ACD, XcpServerTask) | Talk to these two apps via SCS channels directly | **Unchanged.** Still bridged via `ScsToRos2Bridge`; this config migration does not touch channel-level communication at all |
| **Risk of breaking existing deployments** | N/A | None introduced so far: no YAML file has been deployed anywhere yet, so both apps currently run byte-for-byte identically to before this work started |
| **Verification performed** | N/A | Manual code review only: confirmed no call sites removed, confirmed guarded fallback defaults exactly match prior `.rb` values, confirmed brace/paren balance in all edited files. **No compiler/build environment was available in this environment**, so none of this has actually been built or run |

---

## 4. Files Involved

**New files (this directory and this migration):**
- `lps_sa_job_mgr_app_params.yaml`
- `lps_sa_weigh_app_params.yaml`
- `ConfigMigrationReport.md` (this file)

**Modified source files (all changes additive/guarded, nothing removed):**
- `apps/LpsSaJobMgrApp/LpsSaJobMgrApp.h` — added `buildRosNodeOptionsWithParamsFile()` declaration
- `apps/LpsSaJobMgrApp/LpsSaJobMgrApp.cpp` — added the helper's implementation; moved `rosNode_` construction earlier; added guarded parameter overrides for `storage_root`, `simple_cal_max_trucks_supported`
- `apps/LpsSaWeighApp/LpsSaWeighApp.h` — added `buildRosNodeOptionsWithParamsFile()` declaration
- `apps/LpsSaWeighApp/LpsSaWeighApp.cpp` — same pattern; guarded overrides for `cycle_rate_hz`, `temp_root`, `storage_root`, `cpm_exec_tx_period`
- `apps/LpsSaWeighApp/LpsSaCalibration.cpp` — guarded override for `cpm_exec_rate`

**Untouched (still fully load-bearing, do not delete):**
- `config/LpsSaJobMgrApp.rb`
- `config/LpsSaWeighApp.rb`
- All peer-app `.rb` files referencing these two apps' channels (`ScsToRos2Bridge.rb`, `AutonomyConditionDiagnostics.rb`, `AisJhm2DataServer.rb`, `XcpServerTask.rb`, `WorkOrderAssist.rb`, `LpsSaTotalsApp.rb`, `CycleSeg.rb`, `hornOnStoreTest.rb`, `OperatorIdTest.rb`)
- `config/ApplicationTable.rb`, `config/ExecutionTable_CPM.rb`, `config/AlwaysOnTasks.rb`

---

## 5. Outstanding Work Before This Can Be Considered Complete

Per `config_migration_plan.md` Phase 4 and 5 (not yet executed):

1. **Build verification** — this environment had no compiler/build tree available
   (`ros2_jazzy_sdk`, AIS headers, etc. not present in this checkout) to actually
   compile either app. Must be built via the existing SCons build before trusting
   any of this.
2. **Regression check** — confirm both apps launch and behave identically with
   *no* YAML file present (should be a no-op, since that's the fallback path).
3. **Override check** — deploy the YAML files to `$CAT_CONFIG_DIR/ros2/` and
   confirm both apps pick up the overridden values (via the `AIS_LOG_INFO` lines
   already added, e.g. "Loaded ROS2 params file: ...").
4. **Timing check** — confirm no cycle-timing regression from the added
   parameter-read overhead (compare AIS executive slow-cycle counters, or
   equivalent, between before/after).
5. **Cutover (Phase 5)** — only after 1–4 pass: get sign-off, then (and only then)
   consider removing the migrated values from the `.rb` files — never before
   `task::Task` itself is also being retired, since AIS may still require these
   `.rb` files to exist at startup regardless of what's inside them.
