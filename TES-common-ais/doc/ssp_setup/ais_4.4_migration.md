# AIS 4.3 -> 4.4 Migration

## Overview
The following instructions assume the super project has already integrated the following tags:
- TES-common-ais: 0.18.0
- eta-ais:        AIS_APP_TEMPLATE_4.3.0_ALPHA_05 (or later)

The following aliases are used in this document
- DOC_DIR -> TES-common-ais/doc/ssp_setup

## Migrating a CPM super project from 4.1 to 4.4
1. Checkout tag AIS_APP_TEMPLATE_4.4.0_ALPHA_01 (or later) of eta-ais.  Checkout the desired tag of TES-common-ais (where these instructions are located).

2. Update the ssp Makefile by comparing it to DOC_DIR/ssp_setup/ssp/Makefile. Important changes:
   - TES-common-ais's custom zzzAutostart has been removed, so APP_INIT and RESTART_MON are no longer used and should be removed.
   - AIS_SKIP_LIST_FILE is a new variable that by default points to a list of files to skip in TES-common-ais. This can be replaced with an app specific list to e.g. build an app specific RpaClientTask. It should be passed eta-ais Makefile.
   - The native build directory has changed to build-OCS, so PLATFORM=x86_64-linux-gnu should be replaced with PLATFORM=OCS
   - APP_VERITY_PREFIX no longer needs to be passed to apply_patch_ais_all
   - FileTransferBridgeApp is now built with the current CDA verison in eta-ais and the legacy version in TES-common-ais hsa been removed. CDA_VERSION is no longer supported and should be removed
   - External verities such as CoreInfrastructure, ServiceDashboard, zzDevTools can now be fetched automatically during the build process by adding the verity_ext_% target to verity_all_%. If using CDA (e.g. FileTransferBridgeApp), the CDA_LITE verity must be included in the flash file. If using the Ethernet PGT Server feature of Acd2, the ACommonOSS (or CDA_LITE) and AppAvena verities must be included in the flash file. Repo information is described [below](#external-repos).
   - (ALPHA_03+) The version library is now built using version_info_*env files that are also used to generate the verity names.

3. Update the app level Makefile by comparing it to DOC_DIR/app/Makefile. Important changes:
   - The native build directory has changed to build-OCS, so PLATFORM=$(TARGET_ARCH) should be replaced with PLATFORM=OCS
   - CDA_VERSION and the --cdaVersion option are no longer supported and should be removed
   - $(SDK_CHECKOUT_TARGET) should be removed from the project_% target. The SDK is already checked out during the eta-ais build.

4. Update the app level SConstruct by comparing it to DOC_DIR/app/SConstruct. Important changes:
   - The cdaVersion option is no longer supported and should be removed
   - The step to append PLATFORM to the CDFLAGS should not be done for OCS, since there are namespace conflicts
   - -D_GLIBCXX_USE_CXX11_ABI=0 must be removed

5. Copy the contents of TES-common-ais/prod/machineCommon/content/prod/common/version to CPM_DIR/prod/machineCommon/content/prod/common/version.

6. (ALPHA_03+) Copy DOC_DIR/app/release/version_info_*.env to CPM_DIR/release. Replace the contents with those in version_*.cpp. Delete the version_*.cpp files. Delete CPM_DIR/release/appVeritySettings.sh

7. (ALPHA_03+) <ais/log/AisLogger.h> and the LOG_* macros are deprecated. Replace with <ais/log/AisLogger.h> and AIS_LOG_* macros

8. Run `make clean_all` from the ssp. Any libraries compiled with the ABI=0 will not be compatible with ABI=1.

9. If necessary update the ECM OS to a version that supports the newer OpenSSL. The contents of /home/version_info must indicate a minimum OS verison of:
    - A6N1_OS_BLUE_2021.2.0
    - A6N2_OS_BLUE_2021.2.0
    - D6CX_SDK_2021.2.0

10.  Parameter IDs in Acd2/DatalinkManager have been expanded to 64 bit to support CDA UIDs. To avoid inadvertent downcasting, the id field of datalink::ParameterKey has been made private and must instead be retrieved through the appropriate accessor function: getPid(), getCatExtId(), getUid(), etc... For consistency, type must also be retrieved using getType().

## External repos
Repos should be cloned to the following locations ($GITHOME is typically ~/git):

- ACommonOSS - git clone -b ACommonOSS_2021.1.0 --depth 1 git@git1.corp.cat.com:/cat/ess-info/common_oss-a $GITHOME/cat/ess-info/common_oss-a
- AppAvena - git clone -b AVENA_2021.3.0 --depth 1 git@git1.corp.cat.com:/cat/ess-csf/avena-a $GITHOME/cat/ess-csf/avena-a
- CDA - git clone -b CDA_2020.2.0 --depth 1 git@git1.corp.cat.com:/cat/ess-csf/cda-a $GITHOME/cat/ess-csf/cda-a
- CoreInfrastructure - git clone -b CoreTelematics_2020.5.0 --depth 1 git@git1.corp.cat.com:/cat/ess-info/core_telematics-a $GITHOME/cat/ess-info/core_telematics-a
- ServiceDashboard - git clone git@git1.corp.cat.com:/cat/ess-csf/web_manager-a   $GITHOME/cat/ess-csf/web_manager-a
- zzDevTools - git clone git@git1.corp.cat.com:/cat/ess-info/zzdevtools-a $GITHOME/cat/ess-info/zzdevtools-a

## Reducing the size of SCS channels
1. Replace the entire contents of CPM_DIR/prod/common/interfaces/autogen with the file DOC_DIR/app/autogen/generate.pl

2. From the command line, navigate to eta-ais and source changeCatEnvToHere.sh

3. Navigate to CPM_DIR/prod/common/interfaces/autogen. Run the autogenerate.pl script from the command line, passing it the name (directory) of the interface and the options (restorable, typetraits). For example:

   ./autogenerate.pl -i Machine