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
# = Ubuntu_24.04.0 : Ubuntu 24.04 base24-full Docker, native x86_64 build, no SDK
export AIS_DEV_RUNTIME=Ubuntu_14.04.0
export AIS_DEV_RUNTIME_OCS=Ubuntu_18.04.0
export AIS_DEV_RUNTIME_A6N2=Ubuntu_24.04.0
export AIS_DEV_RUNTIME_A7H4=Ubuntu_24.04.0
export DISABLE_GET_DEPS?=0
export DISABLE_UPDATE_DPKG_LIST_DB?=0
export DISABLE_UPDATE_PIP_LIST_DB?=0

# Uncomment to add gdb to ossSoftware
# export DEPS_OSS_GDB_INPUT_CONTENT=1

# Use C++11 on A6N2. Clear this to 
# ENABLE_DYNAMIC_INTERPRETER=no

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
CPM_DIR=CPM-Loader-ais
MONIT_BINARY       = $(CURDIR)/$(CPM_DIR)/tools/$(PLATFORM)/monit
MONIT_CONFIG       = $(CURDIR)/$(CPM_DIR)/config/monitrc
MONIT_JOBMGR_CFG   = $(CURDIR)/$(CPM_DIR)/config/lps_job_mgr.monitrc
MONIT_WEIGH_CFG    = $(CURDIR)/$(CPM_DIR)/config/lps_weigh.monitrc
MONIT_START_SCRIPT = $(CURDIR)/$(CPM_DIR)/scripts/monit_start.sh
MONIT_STOP_SCRIPT  = $(CURDIR)/$(CPM_DIR)/scripts/monit_stop.sh

# RELEASE_DIR is the location of the version_xxx.env files
RELEASE_DIR=${CPM_DIR}/release

# Default MSN in zzzAutostart
DEFAULT_MSN=NOT00000

# Location of www content, relative to ssp.  Comment out if there is none.
CPM_WWW_DIR=./ldpayloadui-a/Web_App_Release_Content
#CPM_WWW_DIR_GEN7=./ldpayloadui-a/Web_App_Release_Content/gen7/browser
CPM_WWW_DIR_GEN7=${CPM_DIR}/patch/gen7/browser

# Prefix for the application verity file.  Used in zzzAutostart.
APP_VERITY_PREFIX=CPM

# Defines the build info for the verity name, located in RELEASE_DIR
VERITY_SETTINGS_FILE=appVeritySettings.sh

# Files to be included in multi-app verity.  Located in CPM_DIR/RELEASE_DIR/VARIANT
MULTIAPP_VERITY_FILE_LIST=cpm_multiapp_files.txt

# Contains paths of modules to skip during eta-ais build, should be relative to build-PLATFORM directory
AIS_SKIP_LIST_FILE=../../${TES_DIR}/patch/eta-ais/skip-list.txt


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
#$(eval include ${RELEASE_DIR}/version_info__common.env)

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
project_a6n2 project_a6n2_% release_a6n2 release_a6n2_% release_only_a6n2 release_only_a6n2_% verities_a6n2 verities_a6n2_% verities-lxc_a6n2_%: AIS_DEV_RUNTIME=${AIS_DEV_RUNTIME_A6N2}
project_a6n2 project_a6n2_% release_a6n2 release_a6n2_% release_only_a6n2 release_only_a6n2_% verities_a6n2 verities_a6n2_% verities-lxc_a6n2_%: CROSS_COMPILE=
project_a6n2 project_a6n2_% release_a6n2 release_a6n2_% release_only_a6n2 release_only_a6n2_% verities_a6n2 verities_a6n2_% verities-lxc_a6n2_%: A6N2_SDK_REPO_TAG=
project_a6n2 project_a6n2_% release_a6n2 release_a6n2_% release_only_a6n2 release_only_a6n2_% verities_a6n2 verities_a6n2_% verities-lxc_a6n2_%: A6N2_TARGET_ARCH=x86_64-linux-gnu
project_a6n2 project_a6n2_% release_a6n2 release_a6n2_% release_only_a6n2 release_only_a6n2_% verities_a6n2 verities_a6n2_% verities-lxc_a6n2_%: NO_SDK_FETCH=1

# Variables for A7H4
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: PLATFORM=A7H4
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: AIS_DEV_RUNTIME=${AIS_DEV_RUNTIME_A7H4}
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: CROSS_COMPILE=$(CURDIR)/${AIS_BUILD_DIR}/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/bin/aarch64-linux-gnu-
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: NO_SDK_FETCH=0
# Gen7 middleware variables for A7H4 sub-builds (TES/CPM)
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_MIDDLEWARE_ENABLED=1
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_MIDDLEWARE_SRC_DIR=ext/middleware-cpp
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_MIDDLEWARE_PROTO_DIR=ext/middleware-proto
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_SSP_DL_SERVICES_DIR=ext/ssp-dl-services
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_MIDDLEWARE_PUGIXML_LIB=:libpugixml.so.1.14
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_MIDDLEWARE_TARGET_ARCH=tgt_gcc_arm64_guest
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: CONAN_TARGET_ARCH=armv8
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: CONAN_HOST_ARCH=x86_64
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_PACKAGE_EXPORT_DIR=ext/gen7_conan_cache
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_PROTOBUF_PACKAGE=protobuf_5_27_0
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_ABSEIL_PACKAGE=abseil_20250127_0
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_FAST_CDR_PACKAGE=cate_fast_cdr_2_3_0
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_FAST_DDS_PACKAGE=cate_fast_dds_3_3_0
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_PROTOC_INTERPRETER=tgt_gcc_9.4.0_ubuntu
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_TARGET_PROTOBUF_DIR=$(GEN7_PACKAGE_EXPORT_DIR)/$(GEN7_PROTOBUF_PACKAGE)/Linux/$(CONAN_TARGET_ARCH)/RelWithDebInfo
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_TARGET_ABSEIL_DIR=$(GEN7_PACKAGE_EXPORT_DIR)/$(GEN7_ABSEIL_PACKAGE)/Linux/$(CONAN_TARGET_ARCH)/RelWithDebInfo
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_TARGET_FAST_CDR_DIR=$(GEN7_PACKAGE_EXPORT_DIR)/$(GEN7_FAST_CDR_PACKAGE)/Linux/$(CONAN_TARGET_ARCH)/RelWithDebInfo
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_TARGET_FAST_DDS_DIR=$(GEN7_PACKAGE_EXPORT_DIR)/$(GEN7_FAST_DDS_PACKAGE)/Linux/$(CONAN_TARGET_ARCH)/RelWithDebInfo
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_HOST_PROTOC_DIR=$(GEN7_PACKAGE_EXPORT_DIR)/$(GEN7_PROTOBUF_PACKAGE)/Linux/$(CONAN_HOST_ARCH)/RelWithDebInfo
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: GEN7_HOST_ABSEIL_DIR=$(GEN7_PACKAGE_EXPORT_DIR)/$(GEN7_ABSEIL_PACKAGE)/Linux/$(CONAN_HOST_ARCH)/RelWithDebInfo
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: CONTAINER_NAME=bogtrotter-user-build-instance
project_a7h4 project_a7h4_% release_a7h4 release_a7h4_% release_only_a7h4 release_only_a7h4_% verities_a7h4 verities_a7h4_% verities-lxc_a7h4_%: ENABLE_DYNAMIC_INTERPRETER=yes

# Variables for OCS
project_ocs project_ocs_% release_ocs release_ocs_% release_only_ocs release_only_ocs_%: PLATFORM=OCS

# Build for ECM (explicitly only supporting specific targets for autocomplete)
project_a6n1: .project_ecm_a6n1 ;
project_a6n2: .project_ecm_a6n2 ;
project_a6n2_adv: .project_ecm_a6n2_adv ;
project_a6n2_sa: .project_ecm_a6n2_sa ;
project_a7h4: .project_ecm_a7h4 ;
project_a7h4_adv: .project_ecm_a7h4_adv ;
project_a7h4_sa: .project_ecm_a7h4_sa ;

release_a6n2_sa_mwl:
	make release_a6n2_sa

release_a6n2_adv_mwl:
	make release_a6n2_adv

verities_a6n2_sa_mwl:
	make verities_a6n2_sa

verities_a6n2_adv_mwl:
	make verities_a6n2_adv

release_a7h4_sa_mwl:
	make release_a7h4_sa

release_a7h4_adv_mwl:
	make release_a7h4_adv

verities_a7h4_sa_mwl:
	make verities_a7h4_sa

verities_a7h4_adv_mwl:
	make verities_a7h4_adv

# Compiling for UBUNTU (OCS/Native)
project_ocs: .project_pre
project_ocs_%: .project_pre
    ### Compile eta-ais first as it is a core dependency.
	@if [ ${SKIP_AIS} != YES ]; then\
		make project PLATFORM=OCS JOBS=${JOBS} BUILD_DIR=${BUILD_DIR} -C ${AIS_DIR} SWVERSION=${SWVERSION} AIS_DEV_RUNTIME=${AIS_DEV_RUNTIME_OCS} APP_BUILD_SYNC_ROOT= DOCKER_CHECKOUT_DISABLE=Y ENABLE_DYNAMIC_INTERPRETER=yes ;\
	fi

	@echo "Copy eta-ais libs to ${TES_DIR}/${BUILD_DIR} for linking (TODO: convert to rsync with symlinks)"
	mkdir -p ${TES_DIR}/${BUILD_DIR}
	cp -r ${AIS_BUILD_DIR}/lib ${TES_DIR}/${BUILD_DIR}
	
	@echo "Building ${TES_DIR}"
	make project PLATFORM=OCS JOBS=$(JOBS) BUILD_DIR=${BUILD_DIR} ENABLE_DYNAMIC_INTERPRETER=yes -C ${TES_DIR}

	@echo "Copy eta-ais & TES-common-ais libs to ${CPM_DIR}/${BUILD_DIR} for linking"
	mkdir -p ${CPM_DIR}/${BUILD_DIR}
	cp -r ${TES_DIR}/${BUILD_DIR}/lib ${CPM_DIR}/${BUILD_DIR}

	@echo "Building ${CPM_DIR}"
	make project PLATFORM=OCS ECM_VARIANT=${ECM_VARIANT} JOBS=$(JOBS) BUILD_DIR=${BUILD_DIR} ENABLE_DYNAMIC_INTERPRETER=yes -C ${CPM_DIR}

    # Change time sync address to blue key (165.26.79.19)
	@sed -i 's/\("timeSyncMasterAddress"     => "165.26.\)[0-9]\+\.[0-9]\+"/\179.19"/' ${AIS_BUILD_DIR}/config/IPAddresses.rb

# Compile all targets.  Add/remove targets as needed
project_all:
	make project_a6n1
	make project_a6n2
	make project_a7h4
	make project_ocs

# Executed before all install/builds. Cannot be built alone
.project_pre:
    # Exit with an error if built from command line
	@test ${PLATFORM}	

	@echo "Checking Ruby syntax in ${TES_DIR} and ${CPM_DIR}"
	@${AIS_DIR}/prod/ais_build_tools/content/check-ruby-syntax.sh -p ${TES_DIR}/config || exit 1
	@${AIS_DIR}/prod/ais_build_tools/content/check-ruby-syntax.sh -p ${CPM_DIR}/config || exit 1

	@echo "Building for ${PLATFORM}"

    # Apply Patches
#	@$(call apply_ais_patch,prod/coretech/ais_task/ais/interfaces/AutonomyConditionMessage/AutonomyConditionRecord.h)
#	@$(call apply_ais_patch,prod/machineCommon/content/prod/infrastructure/appPcm/KeySwitchOnlyShutdown.cpp)
#	@$(call apply_ais_patch,prod/coretech/scripts/launchSystem)
#	@$(call apply_ais_patch,prod/coretech/scripts/StopPrograms.sh)
#	@$(call apply_ais_patch,prod/coretech/ais_pcm/ais/PcmTaskBase/PcmTaskBase.cpp)
#	@$(call apply_ais_patch,prod/ais_build_tools/content/SConsAppInclude.py)
#	@$(call apply_ais_patch,prod/ais_build_tools/content/runtime-build.sh)
#	@$(call apply_ais_patch,prod/ais_build_tools/content/verity-config/zzzAutostart/app_init.sh)
#	@$(call apply_ais_patch,platform/A7H4/libpaths-list.txt)
#	@$(call apply_ais_patch,prod/machineCommon/content/sandbox/testDatalinkManager/SConscript)

    # Apply eta-ais verity patches if they exist
	@if [ -f patch/eta-ais-verity-fixes.patch ]; then \
		echo "Applying verity patches to eta-ais..."; \
		cd ${AIS_DIR} && patch -p1 -N -r - < ${THIS_DIR}patch/eta-ais-verity-fixes.patch 2>/dev/null || true; \
	fi

    # Apply eta-ais conan/remote-order fixes if they exist
	@if [ -f patch/eta-ais-conan-a7h4-fixes.patch ]; then \
		echo "Applying conan patches to eta-ais..."; \
		cd ${AIS_DIR} && patch -p1 -N -r - < ${THIS_DIR}patch/eta-ais-conan-a7h4-fixes.patch 2>/dev/null || true; \
	fi

    # Apply eta-ais build fixes (HOST_MOUNT_ROOT + syncSoftware CAT_DIR fix)
	@if [ -f patch/eta-ais-build-fixes.patch ]; then \
		echo "Applying build fixes to eta-ais..."; \
		cd ${AIS_DIR} && patch -p1 -N -r - < ${THIS_DIR}patch/eta-ais-build-fixes.patch 2>/dev/null || true; \
	fi

    # Apply eta-ais OSS size reduction for A7H4 (remove python + gstreamer from ossSoftware)
	@if [ -f patch/eta-ais-oss-a7h4-fixes.patch ]; then \
		echo "Applying OSS size reduction patches to eta-ais..."; \
		cd ${AIS_DIR} && patch -p1 -N -r - < ${THIS_DIR}patch/eta-ais-oss-a7h4-fixes.patch 2>/dev/null || true; \
	fi
    #scl qualifier read patch - remove once AIS included the SCL qualifier fix included
	@cp patch/libscl_qr_j1939.a ${AIS_DIR}/prod/platformCommon/content/ssp-linux-is7/tgt_gcc_arm64_guest/lib_a4/scl/

    # Create AIS_BUILD_DIR if it doesn't already exist
	@$(call mkdir_safe,${AIS_BUILD_DIR})

# Delete duplicate DataLinkData
	@rm -rf ${AIS_DIR}/prod/machineCommon/content/prod/common/interfaces/DataLinkData/

    # Patch AIS files. See TES-common-ais Makefile for details
	make apply_patch_ais_all DEFAULT_MSN=${DEFAULT_MSN} -C ${TES_DIR}

    # Patch the version
	@cp ${RELEASE_DIR}/*.env ${AIS_DIR}/release
    
    # copy the version_info for the variant  
	@if [ -f ${RELEASE_DIR}/version_info_$(shell echo ${PLATFORM} | tr A-Z a-z)_${ECM_VARIANT}.env ]; then \
		cp -f ${RELEASE_DIR}/version_info_$(shell echo ${PLATFORM} | tr A-Z a-z)_${ECM_VARIANT}.env ${AIS_DIR}/release/version_info_$(shell echo ${PLATFORM} | tr A-Z a-z).env; \
	fi

    # Override the SWVERSION
	#$(eval include ${AIS_DIR}/release/version_info_$(shell echo ${PLATFORM} | tr A-Z a-z).env)
	
    # Copy additional files for verity
	@cp ${AIS_DIR}/changeCatEnvToHere.sh ${AIS_BUILD_DIR}

	# Install www
	# Clear www directory in the build dir and copy web content
	@$(call mkdir_clean,${AIS_BUILD_DIR}/www)
		
	# Install certificates
	$(call mkdir_clean,${AIS_BUILD_DIR}/certs)

	@cp ${TES_DIR}/certs/* ${AIS_BUILD_DIR}/certs/

# Common to all embedded targets.  Cannot be built directly from command line
.project_ecm_%: .project_pre_ecm
    # Exit with an error if built from command line
	@./cate_ros2_build.sh

	@test ${PLATFORM}

    # Apply eta-ais platform circular reference patches (no longer needed - upstream removed circular includes)
	#$(call apply_ais_patch,platform/_COMMON/includes-list.txt)
	#$(call apply_ais_patch,platform/_COMMON/libpaths-list.txt)

    ### Patch and build the version
	cp -a ${RELEASE_DIR}/version.cpp ${AIS_DIR}/prod/machineCommon/content/prod/common/version

    # copy legal_for_trade_identifiers.h
	cp -f ${RELEASE_DIR}/legal_for_trade_identifiers.h ${AIS_DIR}/prod/machineCommon/content/prod/common/version

	# Force rebuild of version lib
	@if [ ${SKIP_AIS} != YES ]; then\
		rm -rf ${AIS_BUILD_DIR}/prod/common/version/;\
		rm -f ${AIS_BUILD_DIR}/lib/libversion*;\
		rm -f ${AIS_BUILD_DIR}/lib/libjhm2*;\
	fi

    # Symlink Gen7 ext content from base platform build dir into variant build dir
    # If base build dir doesn't have the content, allow source-sync to fetch it directly
	@if [ "${GEN7_MIDDLEWARE_ENABLED}" = "1" ] && [ -n "${ECM_VARIANT}" ]; then \
		BASE_BUILD_DIR=${AIS_DIR}/build-${PLATFORM}; \
		for d in gen7_conan_cache middleware-cpp middleware-cpp-a middleware-proto ssp-dl-services development-tools; do \
			if [ -d "$${BASE_BUILD_DIR}/ext/$${d}" ] && [ ! -e ${AIS_BUILD_DIR}/ext/$${d} ]; then \
				ln -sf $$(realpath "$${BASE_BUILD_DIR}/ext/$${d}") ${AIS_BUILD_DIR}/ext/$${d}; \
			fi; \
		done; \
	fi

    # Generate Gen7 middleware protobuf files if missing (requires Docker container)
    # Must run before eta-ais scons build since it compiles sources that #include the generated .pb.h files
    # Requires ext/gen7_conan_cache (from source-sync), so run source-sync first if needed
	@if [ "${GEN7_MIDDLEWARE_ENABLED}" = "1" ] && [ ! -f ${AIS_BUILD_DIR}/ext/ssp-dl-services/config/protobuf/SharkConfiguration/SharkConfiguration.pb.h ]; then \
		if [ ! -d ${AIS_BUILD_DIR}/ext/gen7_conan_cache ]; then \
			echo "Running eta-ais source-sync to fetch Gen7 conan cache..."; \
			make source-sync PLATFORM=${PLATFORM} BUILD_DIR=${BUILD_DIR} -C ${AIS_DIR} AIS_DEV_RUNTIME=${AIS_DEV_RUNTIME} CROSS_COMPILE=${CROSS_COMPILE} NO_SDK_FETCH=${NO_SDK_FETCH} GEN7_MIDDLEWARE_ENABLED=${GEN7_MIDDLEWARE_ENABLED}; \
		fi; \
		echo "Generating Gen7 middleware protobuf files..."; \
		CONTAINER_BUILD_DIR="/home/$$(id -un)/repos/$(notdir $(CURDIR))/${AIS_BUILD_DIR}"; \
		CONTAINER_PROTO_ROOT="$${CONTAINER_BUILD_DIR}/ext/ssp-dl-services/config/protobuf"; \
		CONTAINER_MIDDLEWARE="$${CONTAINER_BUILD_DIR}/ext/middleware-proto"; \
		CONTAINER_PROTOC="$${CONTAINER_BUILD_DIR}/${GEN7_HOST_PROTOC_DIR}/bin/protoc"; \
		CONTAINER_ABSEIL_LIB="$${CONTAINER_BUILD_DIR}/${GEN7_HOST_ABSEIL_DIR}/lib"; \
		CONTAINER_PROTOBUF_LIB="$${CONTAINER_BUILD_DIR}/${GEN7_HOST_PROTOC_DIR}/lib"; \
		docker exec ${CONTAINER_NAME} /bin/bash -lc "set -euo pipefail; LD_LIBRARY_PATH=\"$${CONTAINER_ABSEIL_LIB}:$${CONTAINER_PROTOBUF_LIB}\" \"$${CONTAINER_PROTOC}\" --proto_path=\"$${CONTAINER_PROTO_ROOT}/ParameterUnit\" --cpp_out=\"$${CONTAINER_PROTO_ROOT}/ParameterUnit\" \"$${CONTAINER_PROTO_ROOT}/ParameterUnit/ParameterUnit.proto\"" && \
		docker exec ${CONTAINER_NAME} /bin/bash -lc "set -euo pipefail; LD_LIBRARY_PATH=\"$${CONTAINER_ABSEIL_LIB}:$${CONTAINER_PROTOBUF_LIB}\" \"$${CONTAINER_PROTOC}\" --proto_path=\"$${CONTAINER_PROTO_ROOT}/ParameterUnit\" --proto_path=\"$${CONTAINER_PROTO_ROOT}/SharkConfiguration\" --cpp_out=\"$${CONTAINER_PROTO_ROOT}/SharkConfiguration\" \"$${CONTAINER_PROTO_ROOT}/SharkConfiguration/SharkConfiguration.proto\"" && \
		docker exec ${CONTAINER_NAME} /bin/bash -lc "set -euo pipefail; LD_LIBRARY_PATH=\"$${CONTAINER_ABSEIL_LIB}:$${CONTAINER_PROTOBUF_LIB}\" \"$${CONTAINER_PROTOC}\" --proto_path=\"$${CONTAINER_MIDDLEWARE}\" --cpp_out=\"$${CONTAINER_MIDDLEWARE}\" \"$${CONTAINER_MIDDLEWARE}/middleware_parameter.proto\" \"$${CONTAINER_MIDDLEWARE}/middleware_diagnostics_additionalinformation.proto\" \"$${CONTAINER_MIDDLEWARE}/middleware_diagnostics.proto\"" && \
		echo "Gen7 protobuf generation complete."; \
	fi

    ### Compile eta-ais first as it is a core dependency.
	@if [ ${SKIP_AIS} != YES ]; then\
		make project PLATFORM=${PLATFORM} JOBS=${JOBS} BUILD_DIR=${BUILD_DIR} -C ${AIS_DIR} SWVERSION=${SWVERSION} AIS_DEV_RUNTIME=${AIS_DEV_RUNTIME} CROSS_COMPILE=${CROSS_COMPILE} A6N2_SDK_REPO_TAG=${A6N2_SDK_REPO_TAG} A6N2_TARGET_ARCH=${A6N2_TARGET_ARCH} NO_SDK_FETCH=${NO_SDK_FETCH} SKIP_BUILD_SYNC=1 ENABLE_DYNAMIC_INTERPRETER=${ENABLE_DYNAMIC_INTERPRETER} GEN7_MIDDLEWARE_ENABLED=${GEN7_MIDDLEWARE_ENABLED} ;\
	fi

    # Copy Gen7 middleware libs into build lib dir for linking and deployment
	@if [ "${GEN7_MIDDLEWARE_ENABLED}" = "1" ]; then \
		if [ ! -f ${AIS_BUILD_DIR}/lib/libfastdds.so ]; then \
			echo "Copying Fast-DDS/CDR libraries to ${AIS_BUILD_DIR}/lib..."; \
			cp -a ${AIS_BUILD_DIR}/${GEN7_TARGET_FAST_DDS_DIR}/lib/libfastdds.so* ${AIS_BUILD_DIR}/lib/; \
			cp -a ${AIS_BUILD_DIR}/${GEN7_TARGET_FAST_CDR_DIR}/lib/libfastcdr.so* ${AIS_BUILD_DIR}/lib/; \
		fi; \
		if [ ! -f ${AIS_BUILD_DIR}/lib/libprotobuf.so ]; then \
			echo "Copying protobuf/abseil libraries to ${AIS_BUILD_DIR}/lib..."; \
			cp -a ${AIS_BUILD_DIR}/${GEN7_TARGET_PROTOBUF_DIR}/lib/libprotobuf.so* ${AIS_BUILD_DIR}/lib/; \
			cp -a ${AIS_BUILD_DIR}/${GEN7_TARGET_ABSEIL_DIR}/lib/libabsl_*.so* ${AIS_BUILD_DIR}/lib/ 2>/dev/null || true; \
		fi; \
	fi

    # Install lighttpd binary and modules for A7H4
	@if [ "${PLATFORM}" = "A7H4" ]; then \
		echo "Installing lighttpd for A7H4..."; \
		cp -a lighttpd-a/tgt_gcc_arm64_guest/bin/lighttpd ${AIS_BUILD_DIR}/bin/; \
		mkdir -p ${AIS_BUILD_DIR}/lib/lighttpd; \
		cp -a lighttpd-a/tgt_gcc_arm64_guest/lib/*.so ${AIS_BUILD_DIR}/lib/lighttpd/; \
		echo "copying ROS2 libraries..."; \
        cp -r ${PWD}/ros2_jazzy_sdk/lib/* ${AIS_BUILD_DIR}/lib/; \
        cp -r ${PWD}/ros2_models/lib/cpm_common_interfaces/* ${AIS_BUILD_DIR}/lib/; \
        cp -r ${PWD}/ros2_models/lib/job_mgr_interfaces/* ${AIS_BUILD_DIR}/lib/; \
        cp -r ${PWD}/ros2_models/lib/weigh_app_interfaces/* ${AIS_BUILD_DIR}/lib/; \
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

    # Symlink gen7 conan cache so protobuf paths resolve in TES/CPM builds
    # Check variant build dir first, fall back to base build dir (standalone build uses build-${PLATFORM})
	@conan_src=""; \
	if [ -d ${AIS_BUILD_DIR}/ext/gen7_conan_cache ]; then \
		conan_src="$(CURDIR)/${AIS_BUILD_DIR}/ext/gen7_conan_cache"; \
	elif [ -d ${AIS_DIR}/build-${PLATFORM}/ext/gen7_conan_cache ]; then \
		conan_src="$(CURDIR)/${AIS_DIR}/build-${PLATFORM}/ext/gen7_conan_cache"; \
	fi; \
	if [ -n "$$conan_src" ]; then \
		mkdir -p ${TES_DIR}/${BUILD_DIR}/ext; \
		ln -sfn "$$conan_src" ${TES_DIR}/${BUILD_DIR}/ext/gen7_conan_cache; \
	fi

	@echo "Building ${TES_DIR}"
	GEN7_MIDDLEWARE_ENABLED=${GEN7_MIDDLEWARE_ENABLED} \
	GEN7_MIDDLEWARE_SRC_DIR=${GEN7_MIDDLEWARE_SRC_DIR} \
	GEN7_MIDDLEWARE_PROTO_DIR=${GEN7_MIDDLEWARE_PROTO_DIR} \
	GEN7_SSP_DL_SERVICES_DIR=${GEN7_SSP_DL_SERVICES_DIR} \
	GEN7_MIDDLEWARE_PUGIXML_LIB=${GEN7_MIDDLEWARE_PUGIXML_LIB} \
	GEN7_PROTOC_INTERPRETER=${GEN7_PROTOC_INTERPRETER} \
	GEN7_TARGET_PROTOBUF_DIR=${GEN7_TARGET_PROTOBUF_DIR} \
	GEN7_TARGET_ABSEIL_DIR=${GEN7_TARGET_ABSEIL_DIR} \
	GEN7_TARGET_FAST_CDR_DIR=${GEN7_TARGET_FAST_CDR_DIR} \
	GEN7_TARGET_FAST_DDS_DIR=${GEN7_TARGET_FAST_DDS_DIR} \
	make project PLATFORM=${PLATFORM} JOBS=${JOBS} BUILD_DIR=${BUILD_DIR} -C ${TES_DIR} AIS_DEV_RUNTIME=${AIS_DEV_RUNTIME} CROSS_COMPILE=${CROSS_COMPILE} A6N2_SDK_REPO_TAG=${A6N2_SDK_REPO_TAG} A6N2_TARGET_ARCH=${A6N2_TARGET_ARCH} NO_SDK_FETCH=${NO_SDK_FETCH} SKIP_BUILD_SYNC=1 INSTALL_CONFIGDIR=${AIS_BUILD_DIR}/config

	@echo "Copying Web_App_Release_Content from ldpayloadui-a"
	@if [ ! -z "${CPM_WWW_DIR}" ]; then\
		cp -a ${CPM_WWW_DIR}/. ${AIS_BUILD_DIR}/www/gen6;\
		cp -a ${CPM_WWW_DIR_GEN7}/. ${AIS_BUILD_DIR}/www/;\
		cp -pf ${CPM_DIR}/web_init.sh ${AIS_BUILD_DIR};\
	fi

    ### CPM project

    ### CPM project should be compiled last because it contains project specific apps and is dependent on both ais and tes-common
    # Symlink gen7 conan cache for CPM build
	@conan_src=""; \
	if [ -d ${AIS_BUILD_DIR}/ext/gen7_conan_cache ]; then \
		conan_src="$(CURDIR)/${AIS_BUILD_DIR}/ext/gen7_conan_cache"; \
	elif [ -d ${AIS_DIR}/build-${PLATFORM}/ext/gen7_conan_cache ]; then \
		conan_src="$(CURDIR)/${AIS_DIR}/build-${PLATFORM}/ext/gen7_conan_cache"; \
	fi; \
	if [ -n "$$conan_src" ]; then \
		mkdir -p ${CPM_DIR}/${BUILD_DIR}/ext; \
		ln -sfn "$$conan_src" ${CPM_DIR}/${BUILD_DIR}/ext/gen7_conan_cache; \
	fi

	@echo "Building ${CPM_DIR}"
	GEN7_MIDDLEWARE_ENABLED=${GEN7_MIDDLEWARE_ENABLED} \
	GEN7_MIDDLEWARE_SRC_DIR=${GEN7_MIDDLEWARE_SRC_DIR} \
	GEN7_MIDDLEWARE_PROTO_DIR=${GEN7_MIDDLEWARE_PROTO_DIR} \
	GEN7_SSP_DL_SERVICES_DIR=${GEN7_SSP_DL_SERVICES_DIR} \
	GEN7_MIDDLEWARE_PUGIXML_LIB=${GEN7_MIDDLEWARE_PUGIXML_LIB} \
	GEN7_PROTOC_INTERPRETER=${GEN7_PROTOC_INTERPRETER} \
	GEN7_TARGET_PROTOBUF_DIR=${GEN7_TARGET_PROTOBUF_DIR} \
	GEN7_TARGET_ABSEIL_DIR=${GEN7_TARGET_ABSEIL_DIR} \
	GEN7_TARGET_FAST_CDR_DIR=${GEN7_TARGET_FAST_CDR_DIR} \
	GEN7_TARGET_FAST_DDS_DIR=${GEN7_TARGET_FAST_DDS_DIR} \
	make project PLATFORM=${PLATFORM} ECM_VARIANT=${ECM_VARIANT} JOBS=${JOBS} BUILD_DIR=${BUILD_DIR} MULTI_APP=${MULTI_APP} -C ${CPM_DIR} AIS_DEV_RUNTIME=${AIS_DEV_RUNTIME} CROSS_COMPILE=${CROSS_COMPILE} A6N2_SDK_REPO_TAG=${A6N2_SDK_REPO_TAG} A6N2_TARGET_ARCH=${A6N2_TARGET_ARCH}

	cp -rf ${CPM_DIR}/config/* ${AIS_BUILD_DIR}/config
	cp -rf ${CPM_DIR}/ros2_config/LpsSaWeighApp.yaml ${AIS_BUILD_DIR}/config
	rm -f ${AIS_BUILD_DIR}/config/SConscript

	# removing for rebuild throgh conan and avoid dependency failure (unable to avoid from scons script)
    
	rm -f ${AIS_BUILD_DIR}/bin/LpsSaJobMgrApp \
	
	@./CPM-Loader-ais/apps/conan_build.sh & \
    PID=$$!; \
    wait $$PID


	@echo "copying ROS2 share folders..."; \
    mkdir -p ${AIS_BUILD_DIR}/share; \
    cp -r ${PWD}/ros2_sdk/share/* ${AIS_BUILD_DIR}/share/; \
    @echo "copying ROS2 libraries..."; \
    cp -r ${PWD}/ros2_sdk/lib/* ${AIS_BUILD_DIR}/lib/; \
    cp -r ${PWD}/ros2_models/lib/cpm_common_interfaces/* ${AIS_BUILD_DIR}/lib/; \
    cp -r ${PWD}/ros2_models/lib/job_mgr_interfaces/* ${AIS_BUILD_DIR}/lib/; \
    cp -r ${PWD}/ros2_models/lib/weigh_app_interfaces/* ${AIS_BUILD_DIR}/lib/; \
    @echo "copying bashfiles..."; \
    find ${PWD}/ros2_sdk -maxdepth 1 -type f -exec cp -t ${AIS_BUILD_DIR}/ {} + ; \

	$(call install_monit)
# Executed before all install/builds for ECM targets. Cannot be built alone
.project_pre_ecm: .project_pre
    ### Copy web content to www.  cgi should be installed in cgi-bin

    # Clear www and cgi-bin directories in the build dir
	@$(call rmdir_clean,${AIS_BUILD_DIR}/www)
	@$(call rmdir_clean,${AIS_BUILD_DIR}/cgi-bin)

    # Create www and cgi-bin directories in the build dir and copy web content
	@$(call mkdir_clean,${AIS_BUILD_DIR}/www)
	@$(call mkdir_clean,${AIS_BUILD_DIR}/cgi-bin)

    # Copy Chain Certificate files to build directory
	$(call mkdir_clean,${AIS_BUILD_DIR}/certs)
	@cp ${TES_DIR}/certs/* ${AIS_BUILD_DIR}/certs/

# Runs git clean on AIS and gcc clean on all
# These targets don't need BUILD_DIR definediis exact 
clean_all:
	make clean -C ${CPM_DIR}
	make clean -C ${TES_DIR}
	make gitclean -C ${AIS_DIR}
	make clean -C ${AIS_DIR}

# Runs the make project_% and then runs make release_% just on eta-ais.
release_%: project_%
	@echo "Building $@..."
#	$(MAKE) cppcheck

    # Delete release archive
	@rm -f ${AIS_BUILD_DIR}/*.zip
	make $@ BUILD_DIR=${BUILD_DIR} -C ${AIS_DIR} SWVERSION=${SWVERSION} RLS_ZIP_DIRS="${RLS_ZIP_DIRS}" AIS_DEV_RUNTIME=${AIS_DEV_RUNTIME} CROSS_COMPILE=${CROSS_COMPILE} A6N2_SDK_REPO_TAG=${A6N2_SDK_REPO_TAG} A6N2_TARGET_ARCH=${A6N2_TARGET_ARCH} NO_SDK_FETCH=${NO_SDK_FETCH} SKIP_BUILD_SYNC=1

# Runs only make release_% on eta-ais without rebuilding.
release_only_%:
	@echo "Building $@..."
	$(call install_monit)
#	$(MAKE) cppcheck

    # Delete release archive
	@rm -f ${AIS_BUILD_DIR}/*.zip
	make $(shell echo $@ | cut -f1,3,4 -d_) BUILD_DIR=${BUILD_DIR} -C ${AIS_DIR} SWVERSION=${SWVERSION} RLS_ZIP_DIRS="${RLS_ZIP_DIRS}" AIS_DEV_RUNTIME=${AIS_DEV_RUNTIME}  APP_BUILD_SYNC_ROOT=

verities_%:
    # Delete old verities
	@rm -rf ${AIS_BUILD_DIR}/verity
    # Clean out the directory before we put the xml file we want to put there
	@rm -f ${AIS_BUILD_DIR}/prod/machineCommon/content/config/DefaultConfig/config/*.xml

    # Copy the connection manager configuration from CPM repo
	@cp ${CPM_DIR}/config/conn_mgr_xml_configs/conn_mgr_rw_a6n2_cpm.xml ${AIS_BUILD_DIR}/prod/machineCommon/content/config/DefaultConfig/config/conn_mgr_ro.xml

    # Copy the cda configuration from CPM
	@cp ${CPM_DIR}/config/cda_xml_configs/cda_config_rw_a6n2_cpm.xml ${AIS_BUILD_DIR}/prod/machineCommon/content/config/DefaultConfig/config/cda_config_ro.xml

    # Run make verities_% command in eta-ais
	make $@ JOBS=${JOBS} BUILD_DIR=${BUILD_DIR} -C ${AIS_DIR} SWVERSION=${SWVERSION} APP_VERITY_PREFIX=${APP_VERITY_PREFIX} AIS_DEV_RUNTIME=${AIS_DEV_RUNTIME} CROSS_COMPILE=${CROSS_COMPILE} A6N2_SDK_REPO_TAG=${A6N2_SDK_REPO_TAG} A6N2_TARGET_ARCH=${A6N2_TARGET_ARCH} APP_BUILD_SYNC_ROOT= 

# Get some substrings from for the verities-lxc targets
# These can only be used in the context of the recipe for a verities-lxc target
verities-lxc_%: VERITY_PLATFORM=$(word 2,$(subst _, ,$@))
verities-lxc_%: VERITY_VARIANT=$(word 3,$(subst _, ,$@))
verities-lxc_%: VERITY_BUILD_DIR=build-$(shell echo ${VERITY_PLATFORM} | sed 's/[[:lower:]]/\U&/g')$(shell echo -${VERITY_VARIANT} | sed 's/-$$//')
verities-lxc_%: VERITY_AIS_BUILD_DIR=${AIS_DIR}/${VERITY_BUILD_DIR}
verities-lxc_%:
    # Delete old verities
	@rm -rf ${AIS_BUILD_DIR}/verity

    # Clean out the directory before we put the xml file we want to put there
	@rm -f ${AIS_DIR}/prod/machineCommon/content/config/DefaultConfig/config/*.xml

    # Copy the connection manager configuration from CPM repo
	@cp ${TES_DIR}/prod/machineCommon/content/config/DefaultConfig/config/conn_mgr_rw_a6n2_cpm.xml ${AIS_DIR}/prod/machineCommon/content/config/DefaultConfig/config/conn_mgr_ro.xml

    # Copy the cda configuration from CPM
	@cp ${CPM_DIR}/config/cda_xml_configs/cda_config_rw_a6n2_cpm.xml ${AIS_DIR}/prod/machineCommon/content/config/DefaultConfig/config/cda_config_ro.xml

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
define install_monit
	@test -n "$(PLATFORM)" && test -n "$(AIS_BUILD_DIR)"

	@test -s "$(MONIT_BINARY)" || { echo "ERROR: Missing or empty Monit binary: $(MONIT_BINARY)" >&2; exit 1; }
	@test -s "$(MONIT_CONFIG)" || { echo "ERROR: Missing or empty Monit configuration: $(MONIT_CONFIG)" >&2; exit 1; }

	@test -s "$(MONIT_JOBMGR_CFG)" || { echo "ERROR: Missing or empty Monit JobMgr configuration: $(MONIT_JOBMGR_CFG)" >&2; exit 1; }
	@test -s "$(MONIT_WEIGH_CFG)" || { echo "ERROR: Missing or empty Monit Weigh configuration: $(MONIT_WEIGH_CFG)" >&2; exit 1; }

	@test -s "$(MONIT_START_SCRIPT)" || { echo "ERROR: Missing or empty Monit startup script: $(MONIT_START_SCRIPT)" >&2; exit 1; }
	@test -s "$(MONIT_STOP_SCRIPT)" || { echo "ERROR: Missing or empty Monit stop script: $(MONIT_STOP_SCRIPT)" >&2; exit 1; }

	install -D -m 0755 "$(MONIT_BINARY)" "$(AIS_BUILD_DIR)/bin/monit"

	install -D -m 0600 "$(MONIT_CONFIG)" "$(AIS_BUILD_DIR)/config/monitrc"
	install -D -m 0644 "$(MONIT_JOBMGR_CFG)" "$(AIS_BUILD_DIR)/config/lps_job_mgr.monitrc"
	install -D -m 0644 "$(MONIT_WEIGH_CFG)" "$(AIS_BUILD_DIR)/config/lps_weigh.monitrc"

	install -D -m 0755 "$(MONIT_START_SCRIPT)" "$(AIS_BUILD_DIR)/scripts/monit_start.sh"
	install -D -m 0755 "$(MONIT_STOP_SCRIPT)" "$(AIS_BUILD_DIR)/scripts/monit_stop.sh"
endef