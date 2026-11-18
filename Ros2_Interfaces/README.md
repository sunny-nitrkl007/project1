# Porting a legacy AIS interface channel to a ROS2 `.msg`

This is the process for taking a legacy AIS interface channel
(`prod/common/interfaces/<ChannelName>/...`) and turning it into a ROS2
`.msg` file, for porting any app's interfaces. It covers: finding what an
app actually uses, deciding which package a type belongs in, and writing
the `.msg` file.

## Step 1 — Find what the app you're porting actually uses

Grep the app's own source for legacy interface includes and `InterfaceDb`
lookups:

```sh
grep -rn "interfaces/.*InterfaceTypes.h\|InterfaceDb::fetch" apps/<AppName>/
```

Each hit names a channel folder, e.g. `interfaces/LpsSaWeighReqstChannel/`.
That's your list of channels to port for this app. Cross-reference against
`Ros2_Interfaces/src/*/msg/` to see which ones are already done — you may
only need to add a few new ones, not start from zero.

## Step 2 — Find the actual field/type definitions for each channel

Each channel folder has:
- `InterfaceTypes.h` — boilerplate only (`InputInterface<T>`/`OutputInterface<T>`
  typedefs, name registration). Not where the fields are.
- `<ChannelName>.h` — the real struct. This is what you're porting.

Example, `prod/common/interfaces/LpsSaWeighReqstChannel/LpsSaWeighReqstChannel.h`:
```cpp
class LpsSaWeighReqstChannelStorage: public csvable
{
public:
    enum class Command : uint8_t {
        NONE,
        WRITE_OVERLOAD_WARNING_ENABLE,
        ...
    };
    std::string appName;
    uint32_t appRequestId;
    Command command;
    ...
};
```
Every member field becomes a `.msg` field; every `enum class` becomes a
constants block (ROS2 `.msg` has no native enum type — see Step 4).

## Step 3 — Classify every type: does it belong in cpm_common_interfaces, a local package file, or inline?

For each type found in Step 2 (not just the top-level channel struct — any
nested struct/enum it uses too), search the whole tree for every place that
type name appears, then sort the hits into three buckets by folder path:

```sh
grep -rln "<TypeName>" apps/ prod/
```

**Bucket A** — `prod/common/interfaces/<ChannelName>/...` (the channel
struct definitions themselves). Count the distinct `<ChannelName>` folders
that show up. This tells you how many different channels reuse this type —
1 channel, or 2+.

**Bucket B** — `apps/<the OTHER app>/...` — the app that does **not** own
the channel this type was defined in (e.g. for a JobMgr-defined type, this
is `apps/LpsSaWeighApp/`). Any hit here at all means confirmed cross-app
usage.

**Bucket C** — everything else (`apps/<the owning app>/`, or an oddball
location like `prod/infrastructure/...`). The owning app using its own type
is expected, skip it. A hit in an unexpected location needs a manual look —
open it and check whether it's a real `->get(...)` drain of that type, or
an unrelated `static_cast` that just happens to share a name.

**Decision, using only Bucket A's count and Bucket B's presence:**

| Bucket B | Bucket A | → |
|---|---|---|
| any hit | (doesn't matter) | **Promote to `cpm_common_interfaces`.** This overrides everything else — real cross-app usage always wins. |
| empty | 2+ distinct channel folders | **Separate `.msg` file, local to the owning app's own package** (`job_mgr_interfaces`/`weigh_app_interfaces`). Reused within the app, but nobody else needs it. |
| empty | exactly 1 channel folder | **Inline as constants directly in that one channel's `.msg` file.** Nothing else ever references it, a separate file would just be indirection. |

### Worked example from this codebase

`TipOffState` (from JobMgr's `LpsSaJobMgrTxChannel`) — grep showed it used
in both `apps/LpsSaJobMgrApp/` **and** `apps/LpsSaWeighApp/` → Bucket B hit
→ promoted to `cpm_common_interfaces/msg/TipOffState.msg`.

`LpsSaJobMgrManualTipOffState_t`, `LpsSaJobMgrOperationMode_t`, and three
other enums from the same channel — grep showed them used only inside
`LpsSaJobMgrTxChannel`'s own file, nowhere else → Bucket A = 1, Bucket B
empty → inlined as constant blocks directly inside
`job_mgr_interfaces/msg/LpsSaJobMgrTxChannel.msg` (see Step 4 below), no
separate `.msg` file for any of them.

`DispBestBktWt`, `SimpleCalData`, `WeighBktWtAccuracy` — each reused across
multiple JobMgr channels, but never by WeighApp → Bucket A = 2+, Bucket B
empty → each got its own `.msg` file, local to `job_mgr_interfaces`.

## Step 4 — Write the `.msg` file(s)

Syntax rules, with real examples from this codebase:

**A promoted enum** (`cpm_common_interfaces/msg/TipOffState.msg`) — ROS2
`.msg` has no enum type, so this is constants + a field to hold the value:
```
################################################################################
# LpsSaJobMgrTipOffState_t
################################################################################

uint8 PILE_ENABLE=0
uint8 TRUCK_ENABLE=1
uint8 UNAVAILABLE=2

uint8 value
```

**A channel struct with inlined enums, local composed types, and a
cross-package reference, all in one file**
(`job_mgr_interfaces/msg/LpsSaJobMgrTxChannel.msg`):
```
################################################################################
# LpsSaJobMgrManualTipOffState_t    <- inlined, single-channel enum (Step 3 rule 3)
################################################################################

uint8 MAN_TIP_OFF_AVAILABLE=0
uint8 MAN_TIP_OFF_UNAVAILABLE=1
...

################################################################################
# LpsSaJobMgrTxChannelStorage       <- the actual channel struct
################################################################################

int64 time_point_ns
uint8 manual_tip_off_state                              # holds one of the inlined constants above
cpm_common_interfaces/TipOffTriggerType tip_off_trigger_type   # cross-package: package/TypeName
cpm_common_interfaces/TipOffState tip_off_state
DispBestBktWt disp_best_bkt_wt                           # same-package local type: no prefix
SimpleCalData[] simple_cal_data                          # array: TypeName[] field_name
```

Reference for the pieces:
- Primitive fields: `int64`, `uint8`/`uint16`/`uint32`, `float32`, `bool`, `string` — map 1:1 from the C++ struct's member types.
- Constants: `TYPE NAME=value`, grouped under a `####` comment header naming the original C++ enum — keeps the generated file traceable back to its source.
- Same-package type reference: just `TypeName field_name`, no prefix.
- Cross-package type reference: `package_name/TypeName field_name` — only for types that were promoted to `cpm_common_interfaces` per Step 3.
- Arrays: `TypeName[] field_name`.

Where the file goes: `Ros2_Interfaces/src/<package>/msg/<TypeName>.msg`,
where `<package>` is whichever one Step 3 decided on
(`cpm_common_interfaces`, `job_mgr_interfaces`, `weigh_app_interfaces`, or a
new package if you're porting a genuinely new app).

## Step 5 — Register the new `.msg` file(s) in the build

Two files per package, both already exist for the three current packages —
you're just adding lines, not creating new structure.

**`<package>/CMakeLists.txt`** — add the new `.msg` path to the
`rosidl_generate_interfaces()` list:
```cmake
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/TipOffTriggerType.msg"
  "msg/YourNewType.msg"        # <- add here
  ...
)
```

**`<package>/package.xml`** — if your new `.msg` references a type from
*another* package (i.e. you promoted something to `cpm_common_interfaces`,
or you're referencing an existing `cpm_common_interfaces` type for the
first time from this package), add a `<depend>` tag:
```xml
<depend>cpm_common_interfaces</depend>
```
This isn't optional bookkeeping — the build tooling reads this tag to work
out build order automatically. If you reference another package's type
without declaring the `<depend>`, the build may try to compile your package
before the one it needs, and fail with a confusing error rather than a
clear one.

## Common mistakes to check for

- **Skipping the Bucket A/B grep and guessing.** A type that looks
  single-app-only but actually gets read somewhere unexpected (Bucket C,
  the "manual eyeball" case) will silently build fine and then diverge at
  runtime once two packages both define their own copy.
- **Forgetting `<depend>` in `package.xml`** when referencing another
  package's type — breaks automatic build ordering, not just a cosmetic
  omission.
