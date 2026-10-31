########################################################################
# environment/makefiles/tgt_cc32r_4.30_M32R.mk   clearmake -C gnu
########################################################################

CC_ROOT=C:$/MTOOL

ASFLAGS = \
  -m32rx

CFLAGS = $(CTARGET)
CFLAGS += $(CF_O)
CFLAGS += -switch_by_offset

LDFLAGS = \
  -l m32RcR.lib

