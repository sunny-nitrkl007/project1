# This is intended to be run from the eta-ais directory
# make -f eta-ais.mk -C eta-ais
include Makefile

SHELL=/bin/bash

#
# Additional targets
#
SD_DIR=../ServiceDashboard
WASH_DIR=../Wash

###############
# This target is generically for verity_sd_<platform> type targets
# where <platform> gets mapped to an SDKROOT path (specified as a dependency)
# and an uppercase PLATFORM string.
###############
verity_sd_%:  ../ais/ais-sdk-%-a/$(DEBARCH)
	$(MAKE) -f $(firstword $(MAKEFILE_LIST)) \
	SDKROOT=$(shell readlink -m $<) \
	PLATFORM=$(shell echo $@ | cut -f3 -d_ | sed 's/[[:lower:]]/\U&/g') \
	verity_sd

###############
# note: rsync -r --delete guarantees the exact contents of
#       the source directory are sync'd to $(BUILD_DIR) in
#       less steps.
###############
verity_sd: verity_setup
ifneq ($(SYSROOT),/)
	$(SHELL) $(SD_DIR)/extract_and_patch.sh $(BUILD_DIR)
	cd $(BUILD_DIR)/ServiceDashboard && \
		zip --symlinks -r ServiceDashboard.zip . && \
		cd .. && \
		APPNAME=ServiceDashboard bash $(VERITY_BUILD_SCRIPT) -z ServiceDashboard/ServiceDashboard.zip
else
	@echo "$@ not required when SYSROOT=$(SYSROOT)"
endif

###############
# This target is generically for verity_wash_<platform> type targets
# where <platform> gets mapped to an SDKROOT path (specified as a dependency)
# and an uppercase PLATFORM string.
###############
verity_wash_%:  ../ais/ais-sdk-%-a/$(DEBARCH)
	$(MAKE) -f $(firstword $(MAKEFILE_LIST)) \
	SDKROOT=$(shell readlink -m $<) \
	PLATFORM=$(shell echo $@ | cut -f3 -d_ | sed 's/[[:lower:]]/\U&/g') \
	verity_wash

###############
# note: rsync -r --delete guarantees the exact contents of
#       the source directory are sync'd to $(BUILD_DIR) in
#       less steps.
###############
verity_wash: verity_setup
ifneq ($(SYSROOT),/)
	$(SHELL) $(WASH_DIR)/build_wash.sh $(BUILD_DIR)
	cd $(BUILD_DIR)/Wash && \
		zip --symlinks -r Wash.zip . && \
		cd .. && \
		APPNAME=Wash bash $(VERITY_BUILD_SCRIPT) -z Wash/Wash.zip
else
	@echo "$@ not required when SYSROOT=$(SYSROOT)"
endif

