########################################################################
# environment/makefiles/release.mk                clearmake -C gnu
########################################################################

# This can recursively build a release for all targets.

OS := $(OS)

include tools_$OS.mk

REL_ROOT := ..$/..

VOB_ROOT := $(CLEARCASE_ROOT)
MK_DIR := $(REL_ROOT)$/build$/makefiles
MK_DIR2 := $(VOB_ROOT)$/lib_a4$/release_new$/environment$/makefiles

TGT_ROOT := $(REL_ROOT)
TGT_ARCHS = tgt_diab_4.4a_PPC555EH \
            tgt_diab_4.2b_PPC555EH \
            tgt_diab_4.2b_PPC555EHST \
            tgt_diab_4.4a_PPC555EH_dbg \
            tgt_diab_4.2b_PPC555EH_dbg \
            tgt_rvct_2.1_ARM7TDMI \
            tgt_rvct_2.1_ARM7TDMIST \
            tgt_rvct_2.1_ARM7TDMI_dbg \
            tgt_rvct_2.1_ARM7TDMIST_dbg \
            tgt_gcc_4.0.2_8540 \
            tgt_gcc_4.0.2_8540_dbg \
            tgt_diab_5.5.1.0_PPCVLEEF \
            tgt_diab_5.5.1.0_PPCVLEEF_dbg

TGT_DIRS := $(TGT_ARCHS:tgt_%=$(TGT_ROOT)$/tgt_%)

TGT_MAKEFILES := $(TGT_DIRS:%=%$/Makefile)


.PRECIOUS: $(TGT_ARCHS) libs apps

help:
	@$(ECHO)Targets:$(ECHOEND) 
	@$(ECHO)  all - libs and apps for all target architectures$(ECHOEND) 
	@$(ECHO)  targets - apply to all target architectures$(ECHOEND) 
	$(foreach i,$(TGT_ARCHS), @$(ECHO)     $(i)$(ECHOEND) &)
	@$(ECHO)    - apply to specific target architectures$(ECHOEND) 
	@$(ECHO)  libs - build all libs for specified target architectures$(ECHOEND) 
	@$(ECHO)  apps - build all apps for specified target architectures$(ECHOEND) 
	@$(ECHOEMPTY) 


all: targets libs apps

targets: $(TGT_ARCHS) 

libs:

apps:

clean:
	
$(TGT_ROOT) $(TGT_DIRS):
	mkdir $@ 

# The order is important
$(TGT_ARCHS): tgt_%: $(TGT_ROOT) $(TGT_ROOT)$/tgt_% $(TGT_ROOT)$/tgt_%$/Makefile
	chdir $(TGT_ROOT)$/$@ && "$(MAKE)" $(MAKECMDGOALS)

#	bash -c "mkdir $@" 

$(TGT_MAKEFILES): %$/Makefile:
	$(ECHO)\# $@$(ECHOEND)>$@_banner
	$(CAT) \
	  $@_banner $(CAT_SEPARATOR) \
	  $(MK_DIR2)$/tools_$(OS).mk $(CAT_SEPARATOR) \
	  $(MK_DIR2)$/target.mk $(CAT_SEPARATOR) \
	  $(MK_DIR2)$/defs.mk $(CAT_SEPARATOR) \
	  $(MK_DIR2)$/$(notdir $(patsubst %$/,%,)$(@D)).mk $(CAT_SEPARATOR)	\
	  $(MK_DIR2)$/$(notdir $(patsubst %$/,%,)$(@D))_base.mk $(CAT_SEPARATOR)	\
	  $(MK_DIR)$/defs.mk $(CAT_SEPARATOR) \
	  $(MK_DIR)$/$(notdir $(patsubst %$/,%,)$(@D)).mk $(CAT_SEPARATOR)	\
	  $(MK_DIR2)$/rules.mk $(CAT_OUT_PREFIX) $@
	@-$(RM) $@_banner

 
