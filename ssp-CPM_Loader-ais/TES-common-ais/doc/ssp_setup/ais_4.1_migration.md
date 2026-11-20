# AIS 4.0 -> 4.1 Migration

## Overview
    The following instructions assume the super project has already integrated the following tags:
        TES-common-ais: 0.7.0
        eta-ais:        AIS_APP_TEMPLATE_4.0.0_ALPHA_33

    The following aliases are used in this document
        DOC_DIR -> TES-common-ais/doc/ssp_setup

## Migrating a CPM super project from 4.0 to 4.1
    1. Checkout tag AIS_APP_TEMPLATE_4.1.0_ALPHA_11 of eta-ais.  Checkout the desired tag of TES-common-ais (where these instructions are located).

    2. Copy DOC_DIR/SSP-DIR/Makefile to the base directory of the super project (SSP).  Delete verity_a6n2.sh and verity_autostart.sh

    3. Update the following variables in the Makefile as needed:

        CPM_DIR
        RELEASE_DIR
        DEFAULT_MSN
        CPM_WWW_DIR
        DATATYPETABLE
        DATETIME_FILE
        VERITY_SETTINGS_FILE
        APP_INIT

        If the CPM app supports cppcheck, add it to release_% and release_only_% targets.

        If certain TES Common apps should be disabled for all builds, update the appropriate section of .project_ecm_%

    3. (a) (Variant Targets) if any variant targets do not have www content, put conditions statements in the .project_pre to disable syncing.

        In the SSP Makefile, uncomment out project_a6n2_adv and project_a6n2_sa targets.  Replace adv and sa with applicable variant names.  Add new variants if needed.

        If certain TES Common apps should be disabled for certain targets, update the appropriate section of .project_ecm_%

    4. Copy DOC_DIR/app/release/appVeritySettings.sh to RELEASE_DIR and update with the values from RELEASE_DIR/buildVeritySettings.sh.  Delete RELEASE_DIR/buildVeritySettings.sh and RELEASE_DIR/SConscript.

        # Variables to build name of the verity image
        export BUILD_ID=T05
        export SOFTWARE_PNUM=5730462
        export CHANGE_LEVEL=01

    4. (a) (Variant Targets) Replace RELEASE_DIR wth all RELEASE_DIR/<target> directories in the instructions.

    5. By default, the app in CPM_DIR will be installed to /opt/CPM on the ECM.  If this is desired, delete CPM_DIR/release/vehDataDir. Otherwise, update the Makefile to copy CPM_DIR/release/vehDataDir to eta-ais rather than patching the eta-ais version.

    6. Add the following to CPM_DIR/.gitignore

        # build-$(PLATFORM) directory
        build-*/

    7. Copy DOC_DIR/app/Makefile and DOC_DIR/app/SConstruct to CPM_DIR.

    7. (a) (Variant Targets) Edit CPM_DIR/Makefile to uncomment out the following line

        # Uncomment to support variant targets
        #VARIANT_TARGETS=1

        Add the variant targets to CPM_DIR/SConstruct (search for --targetAppVariant).

        If certain variant targets have no www content, add them to install black list (search for target_app_variant)

    8. Update SConscript files to replace the relative paths '../eta-ais' with '../../eta-ais' and '#/../' with '#/../../' (there may be other similar substitutions needed).  Either do this manually or use these command at your own risk:

    grep -rl "\.\./eta-ais" --include=SConscript | xargs sed -i 's/\.\.\/eta-ais/\.\.\/\.\.\/eta-ais/g'
    grep -rl "#/\.\./" --include=SConscript | xargs sed -i 's/\#\/\.\.\//\#\.\.\/\.\.\//g'

    For future applications, use instead the absolute paths stored in the env:
    
    AIS_BUILD_DIR            e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais/eta-ais/build-A6N2
    AIS_PLATFORM_COMMON_DIR  e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais/eta-ais/build-A6N2/prod/platformCommon/content/tgt_gcc_5.1.0_a6n2
    APP_BUILD_DIR            e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais/CPM-AT-Coaching-ais/build-A6N2 
    APP_DIR                  e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais/CPM-AT-Coaching-ais 
    SSP_DIR                  e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais
    TES_COMMON_DIR           e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais/TES-common-ais/build-A6N2
    TES_PLATFORM_COMMON_DIR  e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais/TES-common-ais/build-A6N2/prod/platformCommon/content/tgt_gcc_5.1.0_a6n2

    9. Synchronize CPM_DIR/config/AlwaysOnTasks.rb with eta-ais/config/AlwaysOnTasks.rb.  Add ecm to all tasks.  Alternatively, Machines::MachineMap.default can be used if the task will run on OCS and all ECMs.

    Add the following to CPM_DIR/config/AlwaysOnTasks.rb.  By default, any Location Code 0-7 is mapped to 165.26.79.19 (A6N1 and A6N2) in TES_COMMON_DIR/config/ReadLCTask.rb.  To override this mapping, create a ReadLCTask_aux.rb file in CPM_DIR/config.

        # readLCTask task is not needed on A5N6 and OCS
        if (CommonTaskParams::Parameters["spoofDnsName"] != "ocs" && Machines::MachineMap.default != "ocs" && !Machines::MachineMap.default.match(/^auto/)) 
        AuxiliaryProcesses.update({
            "readLCTask" => {
                "machines" => [ 
                                Machines::MachineMap.default,
                                ],
                "executableName" => ENV['CAT_DIR'] + "/bin/readLCTask",
                "autoRestart" => true,
                "timeBetweenRestarts_s" => 2,
                "alwaysOn" => false,    
            },
        } )
        end

    10. Update CPM_DIR/prod/infrastructure/SConscript (and any other applicable SConscripts) to exclude ECM only applications from the native build.  For example:

        # Target only apps
        if (infEnv[ 'PLATFORM' ] not in [ 'x86_64-linux-gnu', 'OCS' ]):
            infEnv.buildit( 'aisJhm', ['suse'] )
            infEnv.buildit( 'autonomyConditionDiagnostics', ['suse'] )
            infEnv.buildit( 'baseMachineInterface', ['suse'] )

    11. If aisJhm is installed in the CPM app, replace AisJhm2WebResponses.h (if present) with DOC_DIR/app/jhm2/AisJhm2WebResponses.h (typical path: CPM_DIR/prod/infrastructure/aisJhm/aisJhm2/aisJhm2DataServer/AisJhm2WebResponses.h).  This fixes a bug where the virtual function Jhm2Msg::getJson in TES Common was not being overridden due to the addition of a "const" cast.

    12. If custom APP_INIT and RESTART_MON are not needed, delete the CPM_DIR/prod/autostart directory and all of its contents.

    13. Copy DOC_DIR/app/platform directory it its entirety to CPM_DIR.

    14. (Optional) Migrate ACD changes.  Using LMT as an example:

    Copy over all files except for the following (any changes here must be manually merged):

                File Name                                            Minimum changes needed
    --------------------------------      ------------------------------------------------------------------------
    AutoGenDiagnostics.cpp                Delete file
    AutonomyConditionDiagnostics.cpp      Replace initializeAutoGenDiagEvents with initializeBaseMachineDiagEvents.  Merge SystemHardwareHealth updates.
    AutonomyConditionDiagnostics.h        Replace initializeAutoGenDiagEvents with initializeBaseMachineDiagEvents
    SConscript                            Replace AutoGenDiagnostics.cpp with BaseMachineDiagnostics.cpp.  Add missing libraries/files.
    src_catdl/app_catdl_init.c            PIDs such as F82D should be defined here
    src_catdl/app_catdl_init.h            PIDs such as F82D should be declared extern here
    src_j1939/app_can_init.c              Might need to add: #include "../src_catdl/app_catdl_init.h"
    src_j1939/app_can_init.h              May not need any changes
    src_j1939/app_et_j1939_support.c      May not need any changes
    src_j1939/app_et_j1939_support.h      May not need any changes
    src_j1939/app_j1939_map.c             Delete PID definitions if they are duplicated from app_catdl_init.c
    src_j1939/app_j1939_map.h             Delete PID declarations if they are duplicated from app_catdl_init.h
    src_scl_info/app_scl_obd_es_config.c  Remove diagnosticEventConfig/auto_gen* includes

    15. CPM_DIR/prod/infrastructure/aisJhm/aisJhm2/aisJhm2DataServer/SConscript: Change ../../ to ../ in sourceFiles

    16. (Optional) Update POSE lib to latest version (e.g. AIS_CMD_POSE_LIB_REL_4.10.0_ALPHA_01).

    17. (Optional) Update the SSP Makefile 'project_all' target to only include the desired platforms.

    18. Replace CPM_DIR/release/version_xxx.cpp with the DOC_DIR/app/release/version_a6n2.cpp and update the necessary fields.  Note that swversion is deprecated in favor of the software group fields.

    18. (a) (Variant Targets) Replace all CPM_DIR/release/<target>/version_xxx.cpp and update.

    19. (CDA 2019.X) Recompile any protobuf files with protoc 3.5.0 as follows:

        export SSP_LINUX_PATH=<ssp-linux repo path>
        cd ${SSP_LINUX_PATH}/lib_oss/grpc-a/tgt_gcc_4.4.3_ubuntu/protoc/protoc
        git checkout gRPC_v1.9.1_2019.1.1

        export PROTO_FILE_PATH=<path to .proto file>
        export PROTO_FILE_NAME=<.proto file name>
        export CPP_FILE_PATH=<path where pb.cpp and pb.h files are to be stored>
        ${SSP_LINUX_PATH}/lib_oss/grpc-a/tgt_gcc_4.4.3_ubuntu/protoc/protoc --proto_path=${SSP_LINUX_PATH}/ssp-cda/cda-a/:${PROTO_FILE_PATH} --cpp_out=${CPP_FILE_PATH} ${PROTO_FILE_PATH}/${PROTO_FILE_NAME}

        EXAMPLE VARIABLES:

        export SSP_LINUX_PATH=~/git/ssp-linux
        export PROTO_FILE_PATH=~/git/ssp-CPM_Tpms2-ais/cpm-tpms2-ais/prod/common/protobuf/TMAC_Telemetry_Transfer
        export PROTO_FILE_NAME=TMAC_Telemetry_Transfer.proto
        export CPP_FILE_PATH=~/git/ssp-CPM_Tpms2-ais/cpm-tpms2-ais/prod/common/protobuf/TMAC_Telemetry_Transfer

    14. Copy DOC_DIR/app/config/SConscript to CPM_DIR/config

    21. (ProductionLogger) Copy DOC_DIR/app/config/DataTypeTable_CPM.rb (suffix must match LOGGER_SUFFIX in the SSP Makefile) to CPM_DIR/config.  Add any CPM Project specific scs channels

        To override any default ProductionLoggers settings, also copy DOC_DIR/app/config/ProductionLogger_CPM.rb  to CPM_DIR/config and rename it to match LOGGER_SUFFIX.

        Delete the following files from CPM_DIR/config if they exist:
            DataTypeTable.rb
            DataTypeTable_MachineCommon.rb
            interfaces.rb
            interfaces_MachineCommon.rb

    22. It is recommended to do a file-by-file comparison of CPM_DIR/config and eta-ais/config as a sanity check.

    23. Replace any instances of writing to "restart.txt" with publishing a SystemRestartRequestOutput: 

        App.rb: (Interfaces.update)
            "SystemRestartRequestOutput" => InterfaceDefs::SystemRestartRequestOutput,

        App.h:
            #include <interfaces/GenericRequest/InterfaceTypes.h>
        
            GenericRequestOutput* systemRestartRequestOutput_;
        
        App.cpp - initialize():
            
    SystemRestartRequestOutput = dynamic_cast<GenericRequestOutput*>( task::InterfaceDb::fetch("SystemRestartRequestOutput"));
            if( NULL == systemRestartRequestOutput_ )
            {
                LOG_FATAL("No System Restart Request Output Channel defined");
                everythingOk = false;
            }
        
        App.cpp - replace restart.txt write:
            GenericRequest systemRestartRequest;
            systemRestartRequest.setRequest(true);
            systemRestartRequest.setRequester("AisJhm2DataServer");
            systemRestartRequestOutput_->publish(systemRestartRequest);

    24. (Optional) Update CPM_DIR/apps/aisXcpServer as follows:

        Delete CPM_DIR/apps/include/xcp_server and CPM_DIR/apps/lib/libxcp_server.a

        Replace CPM_DIR/apps/aisXcpServer/SConscript with DOC_DIR/app/aisXcpServer/SConscript.  If necessary, replace 'testEnv' with the name of /apps scons env name.

        XcpScsInputsDb.h - Delete DB_PUSH macro definitions.  Convert to DB_PUSH_ADDR macros to support xcpable interface (see apps/xcp_server/README for more info).

    25. If there are rapidjson build errors, update the project per the 0.10.0 release notes.

    26. (scenarios) To use scenarios, create CPM_DIR/config/production/ActiveTasks_CPM.rb (the suffix doesn't matter).  This should update SystemTasks with the scenario specifc tasks that should run.  Remove these tasks from CPM_DIR/config/AlwaysOnTasks.rb (which should only include scs and readLCTask if desired).

        If different tasks should run when the MSN is invalid (not found in ApplicationTable.rb), create CPM_DIR/config/production/Unknown/ActiveTasks_CPM.rb.

        Examples can be found in DOC_DIR/app/config/production.

    27. Build the project per TES-common-ais/doc/build_commands.txt

## Build 

    1. If during the build process additional header files are needed, update platform/<PLATFORM>/includes-list.txt.  For additional libraries, update libpaths-list.txt.  For additional source directories, update source_sync.txt.  If there are any required shared libraries that are not already installed by TES-common-ais, add them to libslist.txt.  Note that all paths are relative to the build-<PLATFORM> directory.

    For libs/includes shared between A6N1 and A6N2, update the common platform/A6NX files instead of each platform individually.

    2. If there is a 'multiple definition' linking issue for an app, a temporary solution is to update the SConstruct by uncommenting allow-multiple-definition:

            # append to LINKFLAGS
            # these arguments are joined together with a comma ','
            linkArgs = [ '-Wl',
                        '-E',
                        '--no-as-needed',
                        '--copy-dt-needed',
                        #'--allow-multiple-definition', # workaround until scons files are fixed
                    ]

    Long term, the offending libraries/source files should be fixed.

    3. By default, the following libraries will be used:

    CDA:      CDA_2018.5.0
    gRPC:     grpc_v1.0.0_2018.1.0
    protobuf: 3.0

    To use the latest versions in eta-ais, in the SSP Makefile change the value of CDA_VERSION.  As of this writing, the latest versions are:

    CDA:      CDA_2019.5.0
    gRPC:     gRPC_v1.9.1_2019.2.0
    protobuf: 3.5
