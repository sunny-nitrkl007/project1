########################################################################
# src/makefiles/defs.mk                                 clearmake -C gnu
########################################################################

LIB_A4 = $(VOB_ROOT)$/lib_a4
LIB_SSS = $(VOB_ROOT)$/lib_sss
CRYPTO_ROOT = $(VOB_ROOT)$/cots_nonexport_release$/scl_crypto-a


ifeq ($(findstring tgt_ar_diab_5.9.4.0_PPCVLEEF, $(TGT_ARCH)), tgt_ar_diab_5.9.4.0_PPCVLEEF)

INCS +=  \
 $(I)$(HAL_ROOT)$/include \
 $(I)$(OEL_ROOT)$/include2 \
 $(I)$(SCL_ROOT)$/include \
 $(I)$(SCL_ROOT)$/src$/include_lib \
 $(I)$(CD_ROOT)$/include \
 $(I)$(LIB_A4)$/etpu$/include \
 $(I)$(LIB_A4)$/proto$/boot$/include \
 $(I)$(CRYPTO_ROOT)$/include  \
 $(I)$(OEL_ROOT)$/include \
 $(I)$(LIB_SSS)$/sss$/include
else

INCS +=  \
 $(I)$(HAL_ROOT)$/include \
 $(I)$(OEL_ROOT)$/include \
 $(I)$(SCL_ROOT)$/include \
 $(I)$(SCL_ROOT)$/src$/include_lib \
 $(I)$(CD_ROOT)$/include \
 $(I)$(LIB_A4)$/etpu$/include \
 $(I)$(LIB_A4)$/proto$/boot$/include \
 $(I)$(CRYPTO_ROOT)$/include 
 
endif 

ifeq ($(findstring tgt_diab_5., $(TGT_ARCH)), tgt_diab_5.)	 
INCS +=  \
 $(I)$(REL_ROOT)$/src$/include_lib \
 $(I)$(HAL_ROOT)$/include_test_framework \
 $(I)$(LIB_SSS)$/sss$/include 

endif

