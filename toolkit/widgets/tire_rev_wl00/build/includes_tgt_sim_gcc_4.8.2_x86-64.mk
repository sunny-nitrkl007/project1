#******************************************************************************
# COPYRIGHT (C) 2019 CATERPILLAR INC.   ALL RIGHTS RESERVED.
#
#   FILE:
#       includes_tgt_diab_5.9.4.0_PPCVLEEF.mk
#
#   DESCRIPTION:
#       This is a utility include makefile to define the include search path
#       for this library.
#
#******************************************************************************

#Internal Includes
INC_PATHS_INT += ../include


#External Includes
INC_PATHS_EXT += $(VOB_ROOT)/lib_info_products/pcs-interface/include
INC_PATHS_EXT += $(VOB_ROOT)/lib_info_products/prodcore/include
INC_PATHS_EXT += $(VOB_ROOT)/lib_a4/hal/include
INC_PATHS_EXT += $(VOB_ROOT)/lib_a4/scl/include
INC_PATHS_EXT += $(VOB_ROOT)/lib_oel/oel/include





















