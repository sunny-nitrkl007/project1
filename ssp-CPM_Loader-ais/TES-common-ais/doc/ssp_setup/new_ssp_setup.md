**New CPM Super Project (SSP) Setup**

# Overview
    This document describes the steps for setting up a CPM Super Project (SSP)

    The following aliases are used in this document
        DOC_DIR -> TES-common-ais/doc/ssp_setup

# File Structure
    Create the following following file structure

    SSP-DIR
    ├── ais
    │   └── ais-sdk-a6n2-a     // git@git3.corp.cat.com:/mix/ais/ais-sdk-a6n2-a
    │   └── ais-sdk-a6n1-a     // git@git3.corp.cat.com:/mix/ais/ais-sdk-a6n1-a
    ├── eta-ais                // git@gitgis.ecorp.cat.com:CATE_AIS/ais_app_template.git 
    ├── CPM-Project            // Project Specific Reapo
    ├── Makefile
    ├── README.md
    └── TES-Common-ais         // git@git1.corp.cat.com:/cat/ess-info/TES-common-ais 

# Setting up a CPM SSP
    1. Checkout tag AIS_APP_TEMPLATE_4.1.0_ALPHA_11 of eta-ais.  Checkout the desired tag of TES-common-ais (where these instructions are located).

    2. Copy DOC_DIR/SSP-DIR/Makefile to the base directory of the SSP.

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

    4. Copy DOC_DIR/app/appVeritySettings.sh to RELEASE_DIR and update with the appropriate values.

        # Variables to build name of the verity image
        export BUILD_ID=T05
        export SOFTWARE_PNUM=5730462
        export CHANGE_LEVEL=01

    4. (a) (Variant Targets) Replace RELEASE_DIR wth all RELEASE_DIR/<target> directories in the instructions.

    5. By default, the app in CPM_DIR will be installed to /opt/CPM on the ECM.  If this is not desired, update the Makefile to copy CPM_DIR/release/vehDataDir to eta-ais rather than patching the eta-ais version.

    6. Add the following to CPM_DIR/.gitignore

        # build-$(PLATFORM) directory
        build-*/

    7. Copy DOC_DIR/app/Makefile and DOC_DIR/app/SConstruct to CPM_DIR.

    7. (a) (Variant Targets) Edit CPM_DIR/Makefile to uncomment out the following line

        # Uncomment to support variant targets
        #VARIANT_TARGETS=1

        Add the variant targets to CPM_DIR/SConstruct (search for --targetAppVariant).

        If certain variant targets have no www content, add them to install black list (search for target_app_variant)

    8. Copy necessary apps (jhm2, ACD), SConscripts and config files from eta-ais.

    9. Update CPM project any SConscript files to replace relative paths (e.g. '../eta-ais') with the absolute paths stored in the env:
    
    AIS_BUILD_DIR            e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais/eta-ais/build-A6N2
    AIS_PLATFORM_COMMON_DIR  e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais/eta-ais/build-A6N2/prod/platformCommon/content/tgt_gcc_5.1.0_a6n2
    APP_BUILD_DIR            e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais/CPM-AT-Coaching-ais/build-A6N2 
    APP_DIR                  e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais/CPM-AT-Coaching-ais 
    SSP_DIR                  e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais
    TES_COMMON_DIR           e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais/TES-common-ais/build-A6N2
    TES_PLATFORM_COMMON_DIR  e.g. /home/pf/git/ssp-CPM_AT_Coaching-ais/TES-common-ais/build-A6N2/prod/platformCommon/content/tgt_gcc_5.1.0_a6n2

    10. Copy DOC_DIR/app/platform directory it its entirety to CPM_DIR.

    11. (Optional) Update the SSP Makefile 'project_all' target to only include the desired platforms.

    12. Copy DOC_DIR/app/release/version_a6n2.cpp to CPM_DIR/release/version_xxx.cpp with the and update the necessary fields.  Note that swversion is deprecated in favor of the software group fields.

    12. (a) (Variant Targets) Replace all CPM_DIR/release/<target>/version_xxx.cpp and update.

    13. Compile any protobuf files with protoc 3.5.0 as follows:

        export SSP_LINUX_PATH=<ssp-linux repo path>
        cd ${SSP_LINUX_PATH}/lib_oss/grpc-a/tgt_gcc_4.4.3_ubuntu/protoc/protoc
        git checkout gRPC_v1.9.1_2019.1.1

        export PROTO_FILE_PATH=<path to .proto file>
        export PROTO_FILE_NAME=<.proto file name>
        export CPP_FILE_PATH=<path where pb.cpp and pb.h files are to be stored>
        ${SSP_LINUX_PATH}/lib_oss/grpc-a/tgt_gcc_4.4.3_ubuntu/protoc/protoc --proto_path=${SSP_LINUX_PATH}/ssp-cda/cda-a/:${PROTO_FILE_PATH} --cpp_out=${CPP_FILE_PATH} ${PROTO_FILE_PATH}/${PROTO_FILE_NAME}

        EXAMPLE VARIABLES:

        export SSP_LINUX_PATH=~/git/ssp-linux
        export PROTO_FILE_PATH=~/git/ssp-CPM_Tpms2-ais/TES-common-ais/protobuf/proto/
        export PROTO_FILE_NAME=TMAC_Telemetry_Transfer.proto
        export CPP_FILE_PATH=~/git/ssp-CPM_Tpms2-ais/cpm-tpms2-ais/apps/Tpms2ScoreBoardApp/

    14. Copy DOC_DIR/app/config/SConscript to CPM_DIR/config

    15. (ProductionLogger) Copy DOC_DIR/app/config/DataTypeTable_CPM.rb (suffix must match LOGGER_SUFFIX in the SSP Makefile) to CPM_DIR/config.  Add any CPM Project specific scs channels

        To override any default ProductionLoggers settings, also copy DOC_DIR/app/config/ProductionLogger_CPM.rb  to CPM_DIR/config and rename it to match LOGGER_SUFFIX.

    16. (scenarios) To use scenarios, create CPM_DIR/config/production/ActiveTasks_CPM.rb (the suffix doesn't matter).  This should update SystemTasks with the scenario specifc tasks that should run.  Remove these tasks from CPM_DIR/config/AlwaysOnTasks.rb (which should only include scs and readLCTask if desired).

        If different tasks should run when the MSN is invalid (not found in ApplicationTable.rb), create CPM_DIR/config/production/Unknown/ActiveTasks_CPM.rb.

        Examples can be found in DOC_DIR/app/config/production.

    17. Build the project per TES-common-ais/doc/build_commands.txt

# Build 

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
