########################################################################
# src/makefiles/Makefile                                clearmake -C gnu
########################################################################

# This supports recursive build of a library or application release for
# all supported targets.


# OS - define the host operating system
# Windows NT and 2000 define OS = Windows_NT.
# Default to unix if undefined.
#
OS ?= unix

# TGT_ARCH - Target achitectures supported by this library.  These
# require corresponding makefiles in either MK_DIR or MK_DIR2.
#

ifeq ($(OS),Windows_NT)
TGT_ARCHS += tgt_diab_4.2b_PPC555EH
TGT_ARCHS += tgt_rvct_2.1_ARM7TDMI
TGT_ARCHS += tgt_diab_5.8.0.0_PPCVLEEF
TGT_ARCHS += tgt_cc32r_4.30_M32Rx
TGT_ARCHS += tgt_ar_diab_5.9.4.0_PPCVLEEF
TGT_ARCHS += tgt_sim_gcc_4.8.2_x86-64
else
ifeq ($(OS),unix)
#TGT_ARCHS += tgt_mri_4.5_CPU32
endif
endif


# VOB_ROOT_R - VOB root relative to release directory
#
VOB_ROOT_R = ..$/..

# REL_ROOT_V - release root relative to VOB root
#
REL_ROOT_V = lib_autocode_release$/lib_simulink

# TGT_ROOT - Target build root directory.  This will default to the
# release directory and should not normally be defined here.  If this
# default is used, relative paths will be used in the build scripts.
# If this is defined, absolute paths will be used, supporting target
# builds outside the VOB.  This permits faster development on local
# host drives.	Since users will have different local path names, this
# should be defined on the command line rather than here.  This is
# only required once, when the target structure and makefiles are
# generated.

# ENV_ROOT - Environment root for common makefiles, compilers,
# operating systems, etc.  Can override this on the command line.

########################################################################
#################### DO NOT EDIT THE FOLLOWING #########################
########################################################################

# VOB_ROOT_M - Relative from the src\makefiles directory to the vob root.
VOB_ROOT_M = $(VOB_ROOT_R)$/..$/..

# Provide a default TGT_ROOT directory in case one is not specified from 
# the command line.
TGT_ROOT ?= $(VOB_ROOT_M)$/$(REL_ROOT_V)-a

BACKSLASH := \x
BACKSLASH := $(BACKSLASH:%x=%)

# VOB_ROOT
# Note: non-Clearcase systems will not have CLEARCASE_ROOT defined.
ifeq ($(OS),unix)
ifneq ($(MAKE), clearmake)
  VOB_ROOT = $(abspath $(CURDIR)$/$(VOB_ROOT_M))
else
  VOB_ROOT = $(CLEARCASE_ROOT)$/vobs
endif
else
# OS is not unix.
ifneq ($(MAKE), clearmake)
  # Emake returns the path from abspath with forward slashes.
  # Convert this to backslashes for Windows.
  VOB_ROOT = $(subst /,$(BACKSLASH),$(abspath $(CURDIR)$/$(VOB_ROOT_M)))
else
  VOB_ROOT = $(CLEARCASE_ROOT)
endif
endif

# ENV_ROOT_V - environment root relative to VOB root
#
ENV_ROOT_V = lib_oel$/environment

# ENV_ROOT - environment root
#
ENV_ROOT = $(VOB_ROOT)$/$(ENV_ROOT_V)

# MK_DIR - Release specific makefiles
#
MK_DIR = .

# MK_DIR2 - General shared makefiles
#
MK_DIR2 = $(ENV_ROOT)$/makefiles

# / - Temporary definition of / is required for include path.
#     This limited usage will work on any host.
/ = /


include $(MK_DIR2)$/release.mk

