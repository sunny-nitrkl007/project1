########################################################################
# src/makefiles/tgt_ar_diab_5.9.4.0_PPCVLEEF.mk         clearmake -C gnu
########################################################################

# Use PPCVLEEF:simple instead of the default PPCVLEEN:simple
# This uses the VLE instruction set which saves ROM
# Hardware is used for single-precision floating-point values and 
# software is used for double-precision floating-point values.
CTARGET = -tPPCVLEEF:simple

