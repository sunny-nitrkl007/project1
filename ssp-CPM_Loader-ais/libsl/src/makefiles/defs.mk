########################################################################
# src/makefiles/defs.mk                                 clearmake -C gnu
########################################################################

# This file contains common definitions that are applied to all
# directories in this src tree.



# INCS_HAL_PUBLIC - defines paths to hal public headers
#
# NOTE:  This is temporary until hal is converted to this new
# development structure.  HAL_ROOT is not defined by the standard
# scripts because $(HAL_ROOT)$/include is not valid.  Do NOT use
# the lib_a4/release/include path because it contains alternate
# definitions of C standard and oel headers.
#
# HAL_ROOT = $(VOB_ROOT)$/lib_a4$/proto$/hal
# INCS_HAL_PUBLIC = $(I)$(HAL_ROOT)$/public

# It appears $(HAL_ROOT)$/include is now valid and $(HAL_ROOT) is specified

# INCS - compiler include path option
#
# NOTE:  Use macro $/ for path separators and $(I) for the compiler
# include path option.  These provide target independence.
# The public headers $(I)$(REL_ROOT)$/include and internal
# library scoped headers $(I)$(REL_ROOT)$/src$/include_lib should
# always be included.  Internal directory scoped headers should
# be directly in the source directory, included with #include ""
# (not <>), and the include path is implied and NOT specified.  All
# other headers should be included with #include <>.
#
INCS +=  \
 $(I)$(REL_ROOT)$/include \
 $(I)$(REL_ROOT)$/src$/include_lib


# AGGREGATE_LIBS - defines aggregate libraries
# Archive libraries of objects are created for each library directory.
# These can be combined into aggregate libraries that are independent
# of the directory structure.  A rule will build each aggregate
# library defined by macro AGGREGATE_LIBS.  The constituent libraries
# are defined by defining an explicit dependency of each aggregate
# on its constituents.  Example from oel:
# 
# AGGREGATE_LIBS = lib$/liboel_osek.a lib$/liboel_ose.a
#
# lib$/liboel_osek.a: \
#   lib$/liboel_.a \
#   lib$/liboel_a3g.a \
#   lib$/liboel_rtos.a \
#   lib$/liboel_rtos_osek.a \
#   lib$/liboel_legacy_osek.a
#
# lib$/liboel_ose.a: \
#   lib$/liboel_.a \
#   lib$/liboel_a3g.a \
#   lib$/liboel_rtos.a \
#   lib$/liboel_rtos_ose.a
AGGREGATE_LIBS = lib$/libsl_common.a

# sl_common.a is a collection of everything
#  - Not tied to a particular processor
#  - Not tied to a particular Simulink release
lib$/libsl_common.a: \
	lib$/libsl_cdl.a \
	lib$/libsl_csl.a \
	lib$/libsl_SclJ1939.a \
	lib$/libsl_pms.a \
	lib$/libac_map.a \
	lib$/libsl_cal.a \

# Later if we have more than libsl_perfmon.a tied to a
# processor we can create processor specific libraries.
# libsl_unexpected_reset.a is processor specific, but
# should go away when this functionality is provided by
# core.

