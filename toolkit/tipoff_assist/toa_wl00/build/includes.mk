
#==============================================================================
# COPYRIGHT (C) 2019 CATERPILLAR INC.   ALL RIGHTS RESERVED.
#
#   FILE:
#       includes.mk
#
#   DESCRIPTION:
#       This is a utility include makefile to define the include search path
#       for this library.
#
#==============================================================================

#Internal Includes
INC_PATHS_INT += ../../toa_wl00_x86_64-b/include
INC_PATHS_INT += ../../toa_wl00_inf/include

#External Includes
#INC_PATHS_EXT += $(VOB_ROOT)/lib_a4/hal/include
INC_PATHS_EXT += $(VOB_ROOT)/lib_oel/oel/include
INC_PATHS_EXT += $(VOB_ROOT)/lib_autocode_release/lib_simulink/include_PostR2014a
INC_PATHS_EXT += $(VOB_ROOT)/lib_autocode_release/lib_simulink/include
INC_PATHS_EXT += $(VOB_ROOT)/lib_standards/c/include

INC_PATHS_EXT += $(VOB_ROOT)/lib_math/include
#INC_PATHS_EXT += $(VOB_ROOT)/bal_engine_release/core/oel/public

# GCC required library
# For dll generation
LIB_SRCH_PATHS += $(VOB_ROOT)/lib_oel/environment/mingw/lib64