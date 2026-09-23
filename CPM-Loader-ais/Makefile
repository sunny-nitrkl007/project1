#
#
#

#########
# this is the top level directory to this Git repo
#########
export CPM_DIR := $(shell git rev-parse --show-toplevel 2>/dev/null)

# absolute eta-ais directory path
export AIS_DIR := $(abspath $(lastword $(CPM_DIR)/../eta-ais))
export AIS_BUILD_TOOLS := $(abspath $(lastword $(AIS_DIR)/prod/ais_build_tools/content))
export TES_DIR := $(abspath $(lastword $(CPM_DIR)/../TES-common-ais))

# Docker configuration for native A6N2 builds
export DOCKER_REGISTRY?=artifactory
export CORE_DOCKER_IMG_VERSION?=2.0.0-snapshot20251110.1
export CORE_DOCKER_IMG_NAME?=base24-full
DOCKER_REGISTRY_LOWER := $(shell echo "$(DOCKER_REGISTRY)" | tr '[:upper:]' '[:lower:]')
ifeq ($(strip $(DOCKER_REGISTRY_LOWER)),artifactory)
export CORE_DOCKER_IMG_REPO?=cat-docker.artifacts.cat.com/1a-ais-docker
else
export CORE_DOCKER_IMG_REPO?=ghcr.io/cat-autonomy/core_docker
endif
export DOCKER_IMG?=$(strip $(CORE_DOCKER_IMG_REPO))/$(strip $(CORE_DOCKER_IMG_NAME)):$(strip $(CORE_DOCKER_IMG_VERSION))

# copied from  $(AIS_BUILD_TOOLS)/platform/_COMMON/config.mk
export APP_BUILD_CFG_DIR_BASE?=appSoftware

# copied from  $(AIS_DIR)/prod/machineCommon/content/platform/config.mk
ifeq ($(strip $(APP_BUILD_DIRS)),)
APP_BUILD_DIRS  = lib
APP_BUILD_DIRS += bin
APP_BUILD_DIRS += www
APP_BUILD_DIRS += cgi-bin
APP_BUILD_DIRS += scripts
APP_BUILD_DIRS += config
endif
export APP_BUILD_DIRS

#########
# This is the default number of build jobs to run.
#########
ifndef $(JOBS)
	JOBS=10
endif

# Default executables
export RANLIB?=ranlib

#######
#
# BUILD_DIR is the directory in which the build will be performed.
#
# By default, BUILDDIR=build-$(PLATFORM)
#
# To override BUILD_DIR, type:
#
#  % make BUILD_DIR=<exe> <target>
#
#########
ifndef $(BUILD_DIR)
	BUILD_DIR=build-$(PLATFORM)
endif

AIS_BUILD_DIR=$(AIS_DIR)/$(BUILD_DIR)

#########
# define the arguments for 'make project'
# Note: assume this is a cross-compile if target arch is not
# the same as native so the user needs to specify a SYSROOT value
#########
PROJECT_ARGS  =scons
PROJECT_ARGS += -j$(JOBS)
PROJECT_ARGS += --prod
PROJECT_ARGS += --sandbox
PROJECT_ARGS += --apps
PROJECT_ARGS += --configs
#PROJECT_ARGS += --debug=includes,findlibs # debug
#PROJECT_ARGS += --debug=findlibs # debug

# uncomment for build problems with includes and libraries
#PROJECT_ARGS += --debug=includes,findlibs # debug

# uncomment for build problems with libraries
#PROJECT_ARGS += --debug=findlibs # debug

# this is the host's debian architecture
export DEBARCH ?= $(shell dpkg --print-architecture 2>/dev/null)

# this is the host's build distribution
export BUILD_DISTRO ?= $(shell grep ^DISTRIB_RELEASE= /etc/lsb-release 2>/dev/null | cut -f2- -d=)

# clear OCS settings for native build to skip deps step
ifeq ($(filter NATIVE,$(PLATFORM)),$(PLATFORM))
  OCS_SDK_REPO_TAG=
  OCS_SDK_EXT_URL=
  OCS_PLATFORM_COMMON_TARGET=
else
  # Set OCS SDK TAG and EXT URL based on Ubuntu distribution (used for ruby check and OCS build)
  ifneq ($(filter 15.% 14.% 13.% 12.%,$(BUILD_DISTRO)),$(BUILD_DISTRO))
    ifeq ($(filter 16.%,$(BUILD_DISTRO)),$(BUILD_DISTRO))
      # default tag for Ubuntu 16.xx (ABI=0)
      OCS_SDK_REPO_TAG?=AIS_SDK_OCS_A_1.1-0-ALPHA14-TEST02
      OCS_PLATFORM_COMMON_TARGET?=tgt_gcc_4.9.2_d6cx
    else
      # OCS platformCommon should be the same for all Ubuntu versions after 16.xx
      OCS_PLATFORM_COMMON_TARGET?=tgt_gcc_5.1.0_a6n2
      # The OCS AIS SDK content should be tailored to the current
      # BUILD_DISTRO string so that the OCS application runs on the
      # current build machine
      ifeq ($(filter 17.% 18.%,$(BUILD_DISTRO)),$(BUILD_DISTRO))
        # default tag for Ubuntu 17.xx and 18.xx (ABI=1)
        OCS_SDK_REPO_TAG?=AIS_SDK_OCS_A_18.04.0.dev6
      else
        # default tag for Ubuntu 19.xx, 20.xx, and later (ABI=1)
        OCS_SDK_REPO_TAG?=AIS_SDK_OCS_A_20.04.0.dev6
      endif
    endif
    # By initializing this variable you trigger the get-ais-sdk.sh
    # script to pull in the AIS SDK content from this URL
    OCS_SDK_EXT_URL?=git@gitgis.ecorp.cat.com:CATE_AIS/sdk/ais-sdk-ocs-a
  else
    OCS_SDK_REPO_TAG?=
    OCS_SDK_EXT_URL?=
    OCS_PLATFORM_COMMON_TARGET?=tgt_gcc_4.9.2_d6cx
  endif
endif
export OCS_SDK_REPO_TAG
export OCS_SDK_EXT_URL
export OCS_PLATFORM_COMMON_TARGET

# set AIS_SDK_EXT_URL based on PLATFORM
ifeq ($(filter A6N1% A6N2%,$(PLATFORM)),$(PLATFORM))
  AIS_SDK_EXT_URL?=git@gitgis.ecorp.cat.com:CATE_AIS/sdk/ais-sdk-a6n2-a
else
  ifeq ($(filter OCS,$(PLATFORM)),$(PLATFORM))
    AIS_SDK_EXT_URL?=$(OCS_SDK_EXT_URL)
  else
    ifeq ($(filter A7H4 JTX2,$(PLATFORM)),$(PLATFORM))
      AIS_SDK_EXT_URL?=git@gitgis.ecorp.cat.com:CATE_AIS/sdk/ais-sdk-aarch64-a
    endif
  endif
endif
export AIS_SDK_EXT_URL
export AIS_SDK_EXT_ROOT?=ext/$(shell echo $(AIS_SDK_EXT_URL) | cut -f2- -d: | cut -f2- -d/)

ifeq ($(filter NATIVE,$(PLATFORM)),$(PLATFORM))
  ifeq ($(strip $(DEBARCH)),amd64)
    TARGET_ARCH?=x86_64-linux-gnu
  else
    TARGET_ARCH?=i386-linux-gnu
  endif
  SDKROOT?=
  HOSTROOT?=
  SYSROOT?=/
else
  ifeq ($(filter OCS,$(PLATFORM)),$(PLATFORM))
    TARGET_ARCH?=x86_64-linux-gnu
    ifneq ($(strip $(OCS_SDK_REPO_TAG)),)
      SDKROOT?=$(AIS_DIR)/$(BUILD_DIR)/$(AIS_SDK_EXT_ROOT)
      HOSTROOT?=$(SDKROOT)/$(DEBARCH)/host
      SYSROOT?=$(HOSTROOT)/usr/$(TARGET_ARCH)/sysroot
    else
      SDKROOT?=
      HOSTROOT?=
      SYSROOT?=/
    endif

  else
    ifeq ($(filter ZCU104 A6V1,$(PLATFORM)),$(PLATFORM))
      ifeq ($(filter ZCU104,$(PLATFORM)),$(PLATFORM))
        XILINX_SYSROOTS=/opt/pkg/petalinux/sdk/zcu_104/sysroots
      else
        XILINX_SYSROOTS=/opt/pkg/workspace/output/sdk/sysroots
      endif
      TARGET_ARCH?=aarch64-xilinx-linux
      SDKROOT?=$(XILINX_SYSROOTS)/x86_64-petalinux-linux
      HOSTROOT?=$(SDKROOT)/usr/bin/$(TARGET_ARCH)
      SYSROOT?=$(XILINX_SYSROOTS)/$(TARGET_ARCH)
    else
      ifeq ($(filter A6N% D6% A6Z1,$(PLATFORM)),$(PLATFORM))
        TARGET_ARCH?=x86_64-buildroot-linux-gnu
      endif
      ifeq ($(filter A5N6 A6Z1-32,$(PLATFORM)),$(PLATFORM))
        TARGET_ARCH?=i686-buildroot-linux-gnu
      endif
      ifeq ($(filter PL671 T6R7,$(PLATFORM)),$(PLATFORM))
        TARGET_ARCH?=arm-buildroot-linux-gnueabihf
      endif
      ifeq ($(filter PL542 T6R8,$(PLATFORM)),$(PLATFORM))
        TARGET_ARCH?=arm-buildroot-linux-uclibcgnueabi
      endif
      ifeq ($(filter OTS A6Z1-64 A7Z1,$(PLATFORM)),$(PLATFORM))
        TARGET_ARCH?=x86_64-linux-gnu
      endif
      ifeq ($(filter JTX2 A7H4,$(PLATFORM)),$(PLATFORM))
        TARGET_ARCH?=aarch64-linux-gnu
      endif
      # For native A6N2 builds (no SDK), use native sysroot
      ifeq ($(strip $(A6N2_SDK_REPO_TAG)),)
        ifeq ($(filter A6N2,$(PLATFORM)),$(PLATFORM))
          SDKROOT?=
          HOSTROOT?=
          SYSROOT?=/
        else
          SDKROOT?=$(AIS_DIR)/$(BUILD_DIR)/$(AIS_SDK_EXT_ROOT)
          HOSTROOT?=$(SDKROOT)/$(DEBARCH)/host
          SYSROOT?=$(HOSTROOT)/usr/$(TARGET_ARCH)/sysroot
        endif
      else
        SDKROOT?=$(AIS_DIR)/$(BUILD_DIR)/$(AIS_SDK_EXT_ROOT)
        HOSTROOT?=$(SDKROOT)/$(DEBARCH)/host
        SYSROOT?=$(HOSTROOT)/usr/$(TARGET_ARCH)/sysroot
      endif
    endif
  endif
endif
export SDKROOT
export HOSTROOT
export SYSROOT
export TARGET_ARCH

# add cross-compile required args
PROJECT_ARGS += --crossCompile
PROJECT_ARGS += --sdkRoot=$(SDKROOT)
PROJECT_ARGS += --hostRoot=$(HOSTROOT)
PROJECT_ARGS += --sysRoot=$(SYSROOT)

#
# Set CC if it has the default value cc, i.e. has not been overridden
#  => if $(TARGET_ARCH)-gcc exists in $(HOSTROOT)
#     and HOSTROOT is an actual, non-root directory,
#     search there, i.e. if HOSTROOT is empty or is /,
#     then assume we are using the native compiler,
#     but it should be an error if we do not find
#     a $(TARGET_ARCH)-gcc in $(HOSTROOT) otherwise
#
ifeq ($(filter cc,$(CC)),$(CC))
#  ifeq ($(filter OCS OTS A7Z1 NATIVE,$(PLATFORM)),$(PLATFORM))
  ifeq ($(filter X X/,X$(HOSTROOT)),X$(HOSTROOT))
    CC=gcc
  else
    # we should expect a compiler in $(HOSTROOT), but the location
    # depends on the target architecture
    ifeq ($(filter aarch64-xilinx-linux,$(TARGET_ARCH)),$(TARGET_ARCH))
      CC=$(HOSTROOT)/$(TARGET_ARCH)-gcc
    else
      CC=$(HOSTROOT)/usr/bin/$(TARGET_ARCH)-gcc
    endif
  endif
endif

ifeq ($(strip $(CC)),)
$(warning WARNING: CC is not defined for platform=$(PLATFORM))
else
export CC
endif

#
# CC/CPP/CXX/LD/AR/AS/RANLIB/STRIP need to be configured for cross-compile.
# CROSS_COMPILE is the string prior to 'gcc' in the CC path
#
# Default values:
# - CPP:cc -E
# - CXX:g++
# - AR:ar
# - AS:as
# - ld:LD

ifeq ($(strip $(CROSS_COMPILE)),)
export CROSS_COMPILE?=$(patsubst %gcc,%,$(CC))
endif

# CPP is automatically changed when CC is set above, so it cannot currently
# be overridden by the app
ifeq ($(strip $(CPP)),)
export CPP=$(CROSS_COMPILE)cpp
endif

ifeq ($(filter g++,$(CXX)),g++)
CXX=$(CROSS_COMPILE)g++
endif
export CXX

ifeq ($(filter ar,$(AR)),ar)
AR=$(CROSS_COMPILE)ar
endif
export AR

ifeq ($(filter as,$(AS)),as)
AS=$(CROSS_COMPILE)as
endif
export AS

ifeq ($(filter ld,$(LD)),ld)
LD=$(CROSS_COMPILE)ld
endif
export LD

ifeq ($(filter ranlib,$(RANLIB)),ranlib)
RANLIB=$(CROSS_COMPILE)ranlib
endif
export RANLIB

# add these after TARGET_ARCH and PLATFORM are set
PROJECT_ARGS += --targetArch=$(TARGET_ARCH)
PROJECT_ARGS += --platform=$(PLATFORM)

PROJECT_ARGS += --buildDir=$(BUILD_DIR)

usage:
	@echo "Rules are..."
	-@egrep "^[A-Za-z0-9_]+:" Makefile

doxygen:
	cd dox && doxygen

#####
# this is the safer clean which respects your "Untracked files"
#
# If 'git status' shows you have "Untracked files",
# then no clean will occur and you will be told about them.
# otherwise, a 'make gitclean' will be executed (see gitclean: below).
#
# Pro Tip: Make sure .untracked is in .gitignore
#####
clean:
	find . -type d -name 'obj' -exec rm -rf {} +
	rm -rf build-*

#####
# 'make gitclean' utilizes a less safe (but more effective) version of 'git clean'
# that is intended to leave the user with a completely clean working tree,
# i.e. removing all files listed by a 'git ls-files -o' command.
#
# This is a good target to run just prior to building from HEAD.
#
# Regarding the flags passed to 'git clean':
#
#   The -x flag tells git to ignore the .gitignore and exclude rules so that
#   essentially anything listed by 'git ls-files -o' is a removal target.
#
#   The -d option tells git to remove empty directories left after removing files.
#
#   The -f flag forced removal (i.e. no hand-holding).
#
#   A double -f flag will remove directories that have a .git (ie the DFC content).
#
#       If the Git configuration variable clean.requireForce is not set to false,
#       git clean will refuse to delete files or directories unless given -f, -n
#       or -i. Git will refuse to delete directories with .git sub directory or
#       file unless a second -f is given.
#
#####
gitclean:
	git clean -x -d -f -f

hardclean: gitclean
	git reset --hard HEAD

pwd:
	@echo "building from $(PWD)"

# build directory
$(BUILD_DIR):
	mkdir -p $@

# source sync to $(BUILD_DIR)
source_sync: $(BUILD_DIR)
	@echo "syncing source content to $<"
	# create the $(BUILD_DIR) directory containing all needed source code
	rsync -rptl --copy-links --files-from=platform/$(PLATFORM)/$@.txt . $</.

# typical build for this project
project: source_sync
	# go there
	@echo ""
	@echo "building $(PLATFORM) in $(BUILD_DIR)/ with $(PROJECT_ARGS) install"
	@echo ""

	# copy Pose config files to eta-ais
#	cd $(BUILD_DIR) && cp prod/positioningLib/ais_lib_pose/config/*.rb $(AIS_BUILD_DIR)/config

  # copy args-list and skip-list
	cp -r $(TES_DIR)/platform/$(PLATFORM)/appSoftware $(BUILD_DIR)

  # copy platform files (removeBinLibContent.sh, syncSoftwareDirs, etc)
	cp $(BUILD_DIR)/platform/$(PLATFORM)/* $(AIS_BUILD_DIR)

#	@echo "Copy TES & eta-ais libs to ${BUILD_DIR} for linking"
#	mkdir -p $(BUILD_DIR)/lib
#	@if [ -n "$$(ls -A $(TES_DIR)/$(BUILD_DIR)/lib/ 2>/dev/null)" ]; then \
#		cp -r $(TES_DIR)/$(BUILD_DIR)/lib/* $(BUILD_DIR)/lib/; \
#	else \
#		echo "No TES libraries to copy (directory empty or doesn't exist)"; \
#	fi

	# perform the build
	cd $(BUILD_DIR) && \
	export TLD=$(AIS_DIR) && \
	export BUILD_DIR=$(BUILD_DIR) && \
	export BUILD_SIG=$$(cd $(AIS_DIR) && git rev-parse --short HEAD 2>/dev/null || echo unknown) && \
	export DOCKER_HOME=$(HOME) && \
	export DOCKER_UNAME=$$(id -un) && \
	export DOCKER_UID=$$(id -u) && \
	export DOCKER_GROUP=$$(id -gn) && \
	export DOCKER_GID=$$(id -g) && \
	export DOCKER_CLIENT=$$(which docker 2>/dev/null || echo) && \
	export DOCKER_IMG=$(DOCKER_IMG) && \
	export AIS_DEV_RUNTIME=$(AIS_DEV_RUNTIME) && \
	bash $(AIS_BUILD_DIR)/prod/ais_build_tools/content/scons-build.sh APP

	cd ..

cppcheck:
	./scripts/run_cppcheck.sh .

prodReleaseBuilder:
	scripts/productionReleaseBuilder.sh

# NOTE: This is not yet ready for AIS SDK USE!!!
production:
	if test -f production.log ; then rm production.log; fi      # remove any old 'production.log' file
	if test -f production.status; then rm production.status; fi # remove any old 'production.status' file

	# push the current git-id to the build log info
	echo -n "Using GIT ID:" > production.log
	echo `git rev-parse HEAD` >> production.log

	# Clean all the old files
	@echo "\nCleaning old build, please wait..."
	scons -c ${SCONS_PROD_OUTPUT}; \
	rm -rf bin lib www; \
	rm prod/common/version/version.cpp; git checkout prod/common/version/version.cpp

	# Now do the build
	@echo "\nBuilding software (tail -f production.log for status)...\n"
	if scons --ice -j 128 --prod --withoutTests ${SCONS_PROD_OUTPUT} $* >> production.log 2>&1; \
	then \
	  echo "SUCCESS" > production.status && \
	  echo "\nBuild successfull."; \
	else \
	  echo "FAIL" > production.status && \
	  echo "\BUILD FAILURE, end of output (see production.log for more):" && \
	  tail -n 20 production.log; \
	fi

# These commands produce no output that can be tracked, so making them
# phony ensures make will always run the commands
.PHONY: pwd checkout build tests production
