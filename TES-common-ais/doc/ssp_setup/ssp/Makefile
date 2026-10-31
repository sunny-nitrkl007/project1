# CPM Super Project Makefile
ifndef $(JOBS)
	JOBS=10
endif

SHELL=/bin/bash

# configure SDKs based on AIS_DEV_RUNTIME, supported options:
# = Ubuntu_14.04.0 : Ubuntu 14.04 ais-core-docker and OCS runtime, Boost 1.65.1, no ROS support
# = Ubuntu_18.04.0 : Ubuntu 18.04 ais-core-docker and OCS runtime, Boost 1.65.1, ROS melodic
# = Ubuntu_18.04.1 : Ubuntu 18.04 ais-core-docker and OCS runtime, Boost 1.71.0, ROS noetic
# = Ubuntu_18.04.2 : Ubuntu 18.04 ais-core-docker and OCS runtime, Boost 1.71.0, no ROS support
# = Ubuntu_20.04.0 : Ubuntu 20.04 ais-core-docker and OCS runtime, Boost 1.65.1, ROS melodic
# = Ubuntu_20.04.1 : Ubuntu 20.04 ais-core-docker and OCS runtime, Boost 1.71.0, ROS noetic
export AIS_DEV_RUNTIME=Ubuntu_14.04.0

# Global Path names
THIS_DIR=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))
AIS_DIR=eta-ais
TES_DIR=TES-common-ais
CAT_DIR=${PWD}/${AIS_DIR}

# Allow AIS build to be skipped to speed up debugging
ifndef $(SKIP_AIS)
	SKIP_AIS=NO
endif

# Command line option for multi-app (separate aisCPM verity)
ifndef $(MULTI_APP)
	export MULTI_APP=NO
endif

##############################
### Project specific variables

# App project directory name
CPM_DIR=CPM-Loader_Coaching-ais

# RELEASE_DIR is the location of the version_xxx.env files
RELEASE_DIR=${CPM_DIR}/release

# Default MSN in ScriptUtils.sh
DEFAULT_MSN=NOT00000

# Location of www content, relative to ssp.  Comment out if there is none.
CPM_WWW_DIR=ldpayloadui-a/Web_App_Release_Content

# Prefix for the application verity file.
APP_VERITY_PREFIX=CPM

# Defines the build info for the verity name, located in RELEASE_DIR
VERITY_SETTINGS_FILE=appVeritySettings.sh

# Files to be included in multi-app verity.  Located in CPM_DIR/RELEASE_DIR/VARIANT
MULTIAPP_VERITY_FILE_LIST=cpm_multiapp_files.txt

#
# RLS_ZIP_DIRS defines the actual content path names (directories and files) which are
# to be included in RLS_ZIP.  Any directory names given will be recursed fully, so any
# unwanted content in these paths should be excluded via '--exclude=<path>' in RLS_ZIP_ARGS.
#

RLS_ZIP_DIRS  = bin
RLS_ZIP_DIRS += lib
RLS_ZIP_DIRS += www
RLS_ZIP_DIRS += scripts
RLS_ZIP_DIRS += config
RLS_ZIP_DIRS += cgi-bin
RLS_ZIP_DIRS += certs
RLS_ZIP_DIRS += web_init.sh
RLS_ZIP_DIRS += changeCatEnvToHere.sh

# Override the SWVERSION
$(eval include ${RELEASE_DIR}/version_info__common.env)

# Variables for Target Variants (MWL as an example)
project_%_adv release_%_adv release_only_%_adv verities_%_adv verities-lxc_%_adv verity_multiapp_%: ECM_VARIANT=adv
project_%_sa release_%_sa release_only_%_sa verities_%_sa verities-lxc_%_sa verity_multiapp_%: ECM_VARIANT=sa

# Common variables
project_% release_% release_only_% verities_% verities-lxc_% verity_multiapp_%: BUILD_DIR=build-$(shell echo ${PLATFORM}-${ECM_VARIANT} | sed 's/-$$//')
project_% release_% release_only_% verities_% verities-lxc_% verity_multiapp_%: AIS_BUILD_DIR=${AIS_DIR}/${BUILD_DIR}

# Archive location of multi-app verities
ARCHIVE_DIR=${PWD}/${CPM_DIR}-a

# Variables for A6N1
project_a6n1 project_a6n1_% release_a6n1 release_a6n1_% release_only_a6n1 release_only_a6n1_% verities_a6n1 verities_a6n1_% verities-lxc_a6n1_%: PLATFORM=A6N1

# Variables for A6N2
project_a6n2 project_a6n2_% release_a6n2 release_a6n2_% release_only_a6n2 release_only_a6n2_% verities_a6n2 verities_a6n2_% verities-lxc_a6n2_%: PLATFORM=A6N2

# Variables for OCS
project_ocs project_ocs_% release_ocs release_ocs_% release_only_ocs release_only_ocs_%: PLATFORM=OCS

# Build for ECM (explicitly only supporting specific targets for autocomplete)
project_a6n1: .project_ecm_a6n1 ;
project_a6n2: .project_ecm_a6n2 ;
# project_a6n2_adv: .project_ecm_a6n2_adv ;
# project_a6n2_sa: .project_ecm_a6n2_sa ;

# Compiling for UBUNTU (OCS/Native)
project_ocs project_ocs_%: .project_pre
    ### Compile eta-ais first as it is a core dependency.
	@if [ ${SKIP_AIS} != YES ]; then\
		make project PLATFORM=OCS JOBS=${JOBS} BUILD_DIR=${BUILD_DIR} -C ${AIS_DIR} SWVERSION=${SWVERSION} AIS_DEV_RUNTIME=${AIS_DEV_RUNTIME} APP_BUILD_SYNC_ROOT= DOCKER_CHECKOUT_DISABLE=Y ;\
	fi

	@echo "Copy eta-ais libs to ${TES_DIR}/${BUILD_DIR} for linking"
	mkdir -p ${TES_DIR}/${BUILD_DIR}
	cp -r ${AIS_BUILD_DIR}/lib ${TES_DIR}/${BUILD_DIR}
	
	@echo "Building ${TES_DIR}"
	make project PLATFORM=OCS JOBS=$(JOBS) BUILD_DIR=${BUILD_DIR} -C ${TES_DIR}

	@echo "Copy eta-ais & TES-common-ais libs to ${CPM_DIR}/${BUILD_DIR} for linking"
	mkdir -p ${CPM_DIR}/${BUILD_DIR}
	cp -r ${TES_DIR}/${BUILD_DIR}/lib ${CPM_DIR}/${BUILD_DIR}

	@echo "Building ${CPM_DIR}"
	make project PLATFORM=OCS ECM_VARIANT=${ECM_VARIANT} JOBS=$(JOBS) BUILD_DIR=${BUILD_DIR} -C ${CPM_DIR}

# Change time sync address to blue key (165.26.79.19)
	@sed -i 's/\("timeSyncMasterAddress"     => "165.26.\)[0-9]\+\.[0-9]\+"/\179.19"/' ${AIS_BUILD_DIR}/config/IPAddresses.rb

# Compile all targets.  Add/remove targets as needed
project_all:
	make project_a6n1
	make project_a6n2
	make project_ocs

eta_ais_patches:
	@$(call create_ais_patch,prod/infrastructure/appPcm/KeySwitchOnlyShutdown.cpp)
	@$(call create_ais_patch,scripts/launchSystem)
	@$(call create_ais_patch,scripts/StopPrograms.sh)
	@$(call create_ais_patch,platform/A6N1/set_rpath.sh)
	@$(call create_ais_patch,platform/A6N2/set_rpath.sh)
	@$(call create_ais_patch,platform/x86_64-linux-gnu/set_rpath.sh)


# Executed before all install/builds. Cannot be built alone
.project_pre:
    # Exit with an error if built from command line
	@test ${PLATFORM}

	@echo "Checking Ruby syntax in ${TES_DIR} and ${CPM_DIR}"
	@${AIS_DIR}/prod/machineCommon/content/scripts/checkRubySyntax -p ${TES_DIR}/config || exit 1
	@${AIS_DIR}/prod/machineCommon/content/scripts/checkRubySyntax -p ${CPM_DIR}/config || exit 1

	@echo "Building for ${PLATFORM}"

    # Create AIS_BUILD_DIR if it doesn't already exist
	@$(call mkdir_safe,${AIS_BUILD_DIR})

    # Delete duplicate DataLinkData
	@rm -rf ${AIS_DIR}/prod/machineCommon/content/prod/common/interfaces/DataLinkData/

    # Patch AIS files. See TES-common-ais Makefile for details
	make apply_patch_ais_all DEFAULT_MSN=${DEFAULT_MSN} -C ${TES_DIR}

    # Patch the version
	@cp ${RELEASE_DIR}/*.env ${AIS_DIR}/release

    # Copy additional files for verity
	@cp ${AIS_DIR}/changeCatEnvToHere.sh ${AIS_BUILD_DIR}

    # Install www
    # Clear www directory in the build dir and copy web content
	@$(call mkdir_clean,${AIS_BUILD_DIR}/www)

	@if [ ! -z "${CPM_WWW_DIR}" ]; then\
		cp -a ${CPM_WWW_DIR}/. ${AIS_BUILD_DIR}/www;\
		cp ${CPM_DIR}/web_init.sh ${AIS_BUILD_DIR};\
	fi
		
    # Install certificates
	$(call mkdir_clean,${AIS_BUILD_DIR}/certs)

	@cp ${TES_DIR}/certs/* ${AIS_BUILD_DIR}/certs/

# Common to all embedded targets.  Cannot be built directly from command line
.project_ecm_%: .project_pre_ecm
    # Exit with an error if built from command line
	@test ${PLATFORM}

    # Patch TES-common to disable apps for all targets (bmiEthernet and the coaching tasks in this example)
#	@sed -i "s|^\(\s*testEnv.buildit(\s*'BmiEthernet'\)|#\1|" ${TES_DIR}/apps/SConscript;
#	@sed -i "s|^\(\s*testEnv.buildit(\s*'CoachingTaskExample'\)|#\1|" ${TES_DIR}/sandbox/SConscript;
#	@sed -i "s|^\(\s*testEnv.buildit(\s*'CoachingTaskTest'\)|#\1|" ${TES_DIR}/sandbox/SConscript;

    # Patch TES-common to disable apps for specific targets (jhm2 and www for LMT in this example)
#	@if [ ${ECM_VARIANT} == sa ]; then\
#		sed -i "s|^\(\s*commonEnv.buildit( 'jhm2'\)|#\1|" ${TES_DIR}/prod/common/SConscript;\
#		sed -i "s|\['libs', 'bins', 'wwws', 'configs'\]|\['libs', 'bins', 'configs'\]|" ${TES_DIR}/SConstruct;\
#	fi

    ### Compile eta-ais first as it is a core dependency.
	@if [ ${SKIP_AIS} != YES ]; then\
		make project PLATFORM=${PLATFORM} JOBS=${JOBS} BUILD_DIR=${BUILD_DIR} -C ${AIS_DIR} SWVERSION=${SWVERSION} AIS_DEV_RUNTIME=${AIS_DEV_RUNTIME} APP_BUILD_SYNC_ROOT= DOCKER_CHECKOUT_DISABLE=Y;\
	fi

    # Create www dir in case it was deleted
	@$(call mkdir_clean,${AIS_BUILD_DIR}/www)

    # Recompile any protobuf files with protoc 3.5.0 as follows:
    # cd ${SSP_LINUX_PATH}/lib_oss/grpc-a/tgt_gcc_4.4.3_ubuntu/protoc/
    # git checkout gRPC_v1.9.1_2019.1.1
    # ${SSP_LINUX_PATH}/lib_oss/grpc-a/tgt_gcc_4.4.3_ubuntu/protoc/protoc --proto_path=${SSP_LINUX_PATH}/ssp-cda/cda-a/:${PROTO_FILE_PATH} --cpp_out=${CPP_FILE_PATH} ${PROTO_FILE_PATH}/${PROTO_FILE_NAME}

    ### TES-common should be compiled second because it contains the common apps and is dependent only on eta-ais
    # remove .csv files put into config/csvTestInput by eta-ais
	@rm -f ${AIS_BUILD_DIR}/config/csvTestInput/*.csv

	@echo "Copy eta-ais libs to ${TES_DIR}/${BUILD_DIR} for linking"
	cp -r ${AIS_BUILD_DIR}/lib ${TES_DIR}/${BUILD_DIR}

	@echo "Building ${TES_DIR}"
	make project PLATFORM=${PLATFORM} JOBS=${JOBS} BUILD_DIR=${BUILD_DIR} -C ${TES_DIR}

    ### CPM project
    # remove eta-ais/config/flashRemovalFileList.txt , use from CPM/project/config
	@rm -f ${AIS_BUILD_DIR}/config/flashRemovalFileList.txt

	@echo "Copy eta-ais & TES-common-ais libs to ${CPM_DIR}/${BUILD_DIR} for linking"
	cp -r ${TES_DIR}/${BUILD_DIR}/lib ${CPM_DIR}/${BUILD_DIR}
	@cp ${CPM_DIR}/config/flashRemovalFileList.txt ${AIS_BUILD_DIR}/config/

    ### CPM project should be compiled last because it contains project specific apps and is dependent on both ais and tes-common
	@echo "Building ${CPM_DIR}"
	make project PLATFORM=${PLATFORM} ECM_VARIANT=${ECM_VARIANT} JOBS=${JOBS} BUILD_DIR=${BUILD_DIR} MULTI_APP=${MULTI_APP} -C ${CPM_DIR}

# Executed before all install/builds for ECM targets. Cannot be built alone
.project_pre_ecm: .project_pre
    ### Copy web content to www.  cgi should be installed in cgi-bin

    # Clear www and cgi-bin directories in the build dir
	@$(call rmdir_clean,${AIS_BUILD_DIR}/www)
	@$(call rmdir_clean,${AIS_BUILD_DIR}/cgi-bin)

    # Create www and cgi-bin directories in the build dir and copy web content
	@$(call mkdir_clean,${AIS_BUILD_DIR}/www)
	@$(call mkdir_clean,${AIS_BUILD_DIR}/cgi-bin)

	@if [ ! -z "${CPM_WWW_DIR}" ]; then\
		cp -a ${CPM_WWW_DIR}/. ${AIS_BUILD_DIR}/www;\
		cp ${CPM_DIR}/web_init.sh ${AIS_BUILD_DIR};\
		cp -ar ${CPM_DIR}/videos ${AIS_BUILD_DIR}/www;\
		cp -ar ${CPM_DIR}/languages ${AIS_BUILD_DIR}/www;\
	        mkdir -p ${AIS_BUILD_DIR}/www/test;\
		cp ${CPM_DIR}/javascript_client_coaching.html ${AIS_BUILD_DIR}/www/test/index.html;\
	fi

    # Copy Chain Certificate files to build directory
	$(call mkdir_clean,${AIS_BUILD_DIR}/certs)
	@cp ${TES_DIR}/certs/* ${AIS_BUILD_DIR}/certs/

# Runs git clean on AIS and gcc clean on all
# These targets don't need BUILD_DIR defined
clean_all:
	make clean -C ${CPM_DIR}
	make clean -C ${TES_DIR}
	make gitclean -C ${AIS_DIR}
	make clean -C ${AIS_DIR}

# Runs the make project_% and then runs make release_% just on eta-ais.
release_%: project_%
	@echo "Building $@..."
	$(MAKE) cppcheck

    # Delete release archive
	@rm -f ${AIS_BUILD_DIR}/*.zip
	make $@ BUILD_DIR=${BUILD_DIR} -C ${AIS_DIR} SWVERSION=${SWVERSION} RLS_ZIP_DIRS="${RLS_ZIP_DIRS}" APP_BUILD_SYNC_ROOT=

# Runs only make release_% on eta-ais without rebuilding.
release_only_%:
	@echo "Building $@..."
	$(MAKE) cppcheck

    # Delete release archive
	@rm -f ${AIS_BUILD_DIR}/*.zip
	make $(shell echo $@ | cut -f1,3,4 -d_) BUILD_DIR=${BUILD_DIR} -C ${AIS_DIR} SWVERSION=${SWVERSION} RLS_ZIP_DIRS="${RLS_ZIP_DIRS}" APP_BUILD_SYNC_ROOT=

verities_%:
    # Delete old verities
	@rm -rf ${AIS_BUILD_DIR}/verity

    # Run make verities_% command in eta-ais
	make $@ JOBS=${JOBS} BUILD_DIR=${BUILD_DIR} -C ${AIS_DIR} SWVERSION=${SWVERSION} APP_VERITY_PREFIX=${APP_VERITY_PREFIX} APP_BUILD_SYNC_ROOT=

# Get some substrings from for the verities-lxc targets
# These can only be used in the context of the recipe for a verities-lxc target
verities-lxc_%: VERITY_PLATFORM=$(word 2,$(subst _, ,$@))
verities-lxc_%: VERITY_VARIANT=$(word 3,$(subst _, ,$@))
verities-lxc_%: VERITY_BUILD_DIR=build-$(shell echo ${VERITY_PLATFORM} | sed 's/[[:lower:]]/\U&/g')$(shell echo -${VERITY_VARIANT} | sed 's/-$$//')
verities-lxc_%: VERITY_AIS_BUILD_DIR=${AIS_DIR}/${VERITY_BUILD_DIR}
verities-lxc_%:
    # Delete old verities
	@rm -rf ${AIS_BUILD_DIR}/verity

    # Copy the connection manager configuration from TES common
	@cp ${TES_DIR}/prod/machineCommon/content/config/DefaultConfig/config/conn_mgr_rw_a6n2.xml ${VERITY_AIS_BUILD_DIR}/prod/machineCommon/content/config/DefaultConfig/config
	@cp ${TES_DIR}/prod/machineCommon/content/config/DefaultConfig/config/conn_mgr_rw_a6n1.xml ${VERITY_AIS_BUILD_DIR}/prod/machineCommon/content/config/DefaultConfig/config

	make $@ JOBS=${JOBS} BUILD_DIR=${BUILD_DIR} -C ${AIS_DIR} SWVERSION=${SWVERSION} APP_VERITY_PREFIX=${APP_VERITY_PREFIX} APP_BUILD_SYNC_ROOT=

# Multi-app verity
verity_multiapp_%: PLATFORM=$(shell echo $@ | cut -f3 -d_ | sed 's/[[:lower:]]/\U&/g')
verity_multiapp_%: VARIANT=$(shell echo $@ | cut -f4 -d_ )
verity_multiapp_%:
	$(SHELL) ./scripts/create_multiapp_verity.sh ${AIS_DIR} ${BUILD_DIR} ${RELEASE_DIR}/${VARIANT} ${ARCHIVE_DIR} ${VERITY_SETTINGS_FILE} ${RELEASE_DIR}/${VARIANT}/${MULTIAPP_VERITY_FILE_LIST}

# Run cppcheck
# These targets don't need BUILD_DIR defined
.PHONY: cppcheck
	$(MAKE) cppcheck -C ${TES_DIR}
	make cppcheck -C ${CPM_DIR}

# applies patch to AIS file $1 from the patch directory
AIS_PATCH_DIR=${PWD}/patch/eta-ais
define apply_ais_patch
	@cd ${AIS_DIR} && git checkout HEAD $1 && git apply ${AIS_PATCH_DIR}/$1.patch
endef

define create_ais_patch
	@cd ${AIS_DIR} && git diff $1 > ${AIS_PATCH_DIR}/$1.patch
endef


# Deletes file (if present) and creates a directory
# Arguments: Directory path
define mkdir_safe
	@if [ -f "$1" ]; then\
		rm -f "$1";\
	fi
	@if [ ! -d "$1" ]; then\
		mkdir -p "$1";\
	fi
endef

# Clears out a directory and creates a new one
# Arguments: Directory path
define mkdir_clean
	@$(call rmdir_clean,$1)
	@mkdir -p "$1"
endef

# Clears out a directory
# Arguments: Directory path
define rmdir_clean
	@if [ -f "$1" ]; then\
		rm -f "$1";\
	fi
	@if [ -d "$1" ]; then\
		rm -rf "$1";\
	fi
endef
