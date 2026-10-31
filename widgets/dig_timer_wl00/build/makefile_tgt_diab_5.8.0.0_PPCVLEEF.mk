#******************************************************************************
# COPYRIGHT (C) 2021 CATERPILLAR INC.   ALL RIGHTS RESERVED.
#
# FILE:
#   makefile_tgt_diab_5.8.0.0_PPCVLEEF.mk
#
# DESCRIPTION:
#   Makefile for a given target.
#
#******************************************************************************


#############################################################################
# Build Targets

# Default build target
all : liba ;
#############################################################################


#############################################################################
# Target Configuration

#Target
TARGET_NAME    = tgt_diab_5.8.0.0_PPCVLEEF
#############################################################################


#############################################################################
# CTARGET Configuration:

# DTARGET  = PPCVLE
# DOBJECT  = E for ELF EABI conventions
# DFP      = F for 32-bit Hardware/64-bit Software floating point
#          = N for no floating point support
#          = S for Software floating point emulation
# DENVIRON = simple to include libchar.a for basic character input/output

# Target CPU
DTARGET = PPCVLE

# Target Object Format
DOBJECT = E

# Floating Point Support
DFP = F

# Standard C Library Support
DENVIRON = simple

CTARGET = -t$(DTARGET)$(DOBJECT)$(DFP):$(DENVIRON)

#-XO - removed from flags to match up with previous build.
#Flags not removed to keep consistent with other A5 libs.
COMPILE_MINALIGN = ONE
COMPILE_OPTIMIZE = NONE
COMPILE_PASSSOURCE = PASS
#############################################################################


#############################################################################
# The librarie's shared makefile

include lib.mk
#############################################################################


#############################################################################
# Makefiles Includes

include $(VOB_ROOT)/lib_machine/tools/makefile/makefile_lib_x5_00.mk
#############################################################################

