####################################################################
# Copyright Caterpillar Inc. All Rights Reserved
#
# /lib_autocode_release/lib_simulink/makelets/autosar_inc.mk:
# This is a Source Library Makelet which defines the objects to
# compile, the paths where the associated source files are located,
# and the paths to search for headers needed by the source.
####################################################################

INC_PATHS_EXT += $(COMP_ROOT)/lib_autocode_release/lib_simulink/include_autosar
INC_PATHS_EXT += $(COMP_ROOT)/lib_autocode_release/lib_simulink/include

LIB_SRCH_PATHS += $(COMP_ROOT)/lib_autocode_release/lib_simulink-a/tgt_ar_diab_5.9.4.0_PPCVLEEF/lib
LIB_SRCH_NAMES += sl_common
