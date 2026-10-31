# AIS 5.1 -> 6.0 Migration

## Overview
The following instructions assume the super project has already integrated the following tags:
- TES-common-ais: commit 237d9f80874e22ad2b2e5542dd7a6b65362572c7 (origin/machas3_ais_5.1_a05_updates)
- eta-ais:        AIS_APP_TEMPLATE_5.1.0_ALPHA_05 (or later)

The following aliases are used in this document
- DOC_DIR -> TES-common-ais/doc/ssp_setup

## Significant changes for CPM
For full list of changes, see the [App Template Release Notes](../../../eta-ais/release_notes.txt)

The following are new for 6.0.0:
- The Execution field in Ruby configs for tasks is no longer used. PCM now uses an 'ExecutionTable' hash to map instanceName to process name.
- LXC (Linux Container) support is provided with the verities-lxc Makefile target. By default [verity.cfg](../../../eta-ais/prod/machineCommon/content/config/DefaultConfig/config/verity/verity.cfg) is [patched](../../patch/eta-ais/prod/machineCommon/content/config/DefaultConfig/config/verity/verity.cfg.patch) by TES Common.
- To support LXC, [vehDataDir](../../../eta-ais/prod/machineCommon/content/scripts/vehDataDir) now has a host of configurable paths. By default it is [patched](../../patch/eta-ais/prod/machineCommon/content/scripts/vehDataDir.patch) by TES Common.
- [PlatformConfigTask](../../../eta-ais/config/PlatformConfigTask.rb) runs by default to write configuration files to the etc dir for CAN, CDA, key switch, pcm, and timesync. These files are used at key by the zzzAutostart chain of scripts/processes. By default PlatformConfigTask is configured to runOnceOnStartup (will show up as Shutdown in pcmremote but will not result in a TaskCrashed diagnostic).
- StopPrograms.sh has been refactored into a C++ process that is configured by [StopPrograms.rb](../../config/StopPrograms.rb)

The following are inherited from 5.1.0:
- Support for Ubuntu 18.04 and 20.04 build environments
- New AIS SDKs with Boost 1.65 (later versions will support 1.71)
- ReadLCTask by default is configured to runOnceOnStartup
- A new keyswitch IPC is used, requiring the following ECM OS versions:
    - A6N1_OS_BLUE_2021.4.0
    - A6N2_OS_BLUE_2021.6.0
    - D6CX_OS_BLUE_2022.1.0
- Automated test support with Jenkins

## Migrating a CPM super project from 5.1 to 6.0
1. Replace eta-ais submodule repo with git@gitgis.ecorp.cat.com:CATE_AIS/ais_app_template.git. Checkout tag AIS_APP_TEMPLATE_6.0.0_ALPHA_05. Checkout the desired tag of TES-common-ais (where these instructions are located).

2. Update the ssp Makefile by comparing it to DOC_DIR/ssp_setup/ssp/Makefile. Important changes:
   - RLS_ZIP_DIRS defines the actual content path names (directories and files) which are to be included in RLS_ZIP
   - AIS_SKIP_LIST_FILE has been moved to TES Common as a patch
   - The make verity_all_<ecm> target has been replaced with make_verities_<ecm>
   - The Ubuntu & boost versions are configured with the AIS_DEV_RUNTIME variable
   - The eta-ais/<BUILDDIR>/lib directory is copied to TES Common and CPM_DIR for linking/rpath compatiblity
   - By default eta-ais checks out and builds inside AIS docker containers, this is diabled with DOCKER_CHECKOUT_DISABLE=Y

3. Update the app level Makefile by comparing it to DOC_DIR/app/Makefile. Important changes:
   - To simplify how build environment variables are configured, PLATFORM is now passed as part of the `make project` target and is no longer automatically parsed.
   - AIS A6N2 SDK is now AIS_SDK_A6N2_A_2.0-1.dev1
   - AIS_UTIL_SCRIPTS now points to ais_build_tools
   - Use of commit_id.sh is removed

4. Update the app level SConstruct by comparing it to DOC_DIR/app/SConstruct. Important changes:
   - SConsAppInclude is now in AIS_BUILD_TOOLS, and is imported in full

5. Update ActiveTasks as follows:
    - Delete CPM_DIR/config/AlwaysOnTasks.rb.
    - Copy DOC_DIR/app/config/ExecutionTable.rb and ActiveTasks.rb to CPM_DIR/config and update with app specific entries (TES common is covered by ExecutionTable_Common.rb)
    - Rename any ActiveTasks_CPM.rb to ActiveTasks.rb and add to the first line: require "ActiveTasks_Common.rb"
    - Optionally remove all 'Execution' hashes from task config files to avoid confusion.

6. StopPrograms.sh now calls the C++ program stopPrograms that is configured with StopPrograms.rb in TES common.
    - Copy DOC_DIR/app/config/StopPrograms_aux.rb to CPM_DIR/config and update with app specific processes

7. Remove/comment out any uses of application_get_table (this was a deprecated member of lib_module that has been removed)

8. Search and replace:
    - <interfaces/Example/InterfaceTypes.h> with <ais/interfaces/Example/InterfaceTypes.h>
    - <task/commTask/commTask.h> with <commTask/commTask.h>
    - "DatalinkManager_Enums.rb" with "Acd2Task_DatalinkManager_Enums.rb"
    - "AutonomyConditionServer_Enums.rb" with "Acd2Task_AutonomyConditionServer_Enums.rb"
    - "SystemInfo_Enums.rb" with "Acd2Task_SystemInfo_Enums.rb"

9. Copy AIS_DIR/prod/infrastructure/acd2Task/SConscript to CPM_DIR/prod/infrastructure/acd2Task

10. Update the ECM OS with a compatible keyswitch IPC. The contents of /home/version_info must indicate an OS verison of:
    - A6N1_OS_BLUE_2021.4.0
    - A6N2_OS_BLUE_2021.6.0
    - D6CX_OS_BLUE_2022.1.0

11. Replace CPM_DIR/platform with DOC_DIR/app/platform
