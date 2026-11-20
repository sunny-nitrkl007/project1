########################################################################
# environment/makefiles/tgt_cc32r_4.10r1_M32R_base.mk
# clearmake -C gnu
########################################################################

# compiler independent macros for file suffixes
#
EXE_SUFFIX = elf
EXE_SUFFIX_INT = abs
MOT_FROM_EXE_SUFFIX = abs
ELF_FROM_EXE_SUFFIX = abs 
LCF_SUFFIX = mld

# compiler independent values for CF_G
#
CF_G0 := #  no debugger info
CF_G1 := -g#  debugger information (wo line #s)
CF_G2 := -g#  debugger information, limits optimization
CF_G3 := -g#  debugger information

# CF_G - compiler debugger information option
# Used in CFLAGS for independent control of this.
#
CF_G := $(CF_G2)#  default

# compiler independent values for CF_O
#
CF_O0 :=	#  no special optimization
CF_O1 := -O -Ospace
CF_O2 := -O
CF_O3 := -O

# CF_O - compiler optimization option
# Used in CFLAGS for independent control of this.
#
CF_O := $(CF_O3)#  default

# compiler independent values for LD_M
# Must defer evaluation.  Only valid in rules that define $*.
#
#
LD_M0 = #               no map file
LD_M1 = -M $*.map#    brief map file
LD_M2 = -M $*.map#   detailed map file
LD_M3 = -M $*.map#   brief map & Xref
LD_M4 = -M $*.map#   detailed map & Xref

# LD_M - linker map option
# Used in linker command for independent control of this.
#
LD_MF = $(LD_M2)

# LD_LCF - LINK option to use rule prerequisite as a linker command file
# NOTE:  Should be last option since some tools specify it as option argument
# and others list it with object file names that follow all options.  The $<
# is included here so an empty definition can entirely omit the linker
# command file when not used, such as native builds.
#
LD_LCF =

# The following are required for the tool chain.
M32RBIN = $(CC_ROOT)$/bin32R
M32RLIB = $(CC_ROOT)$/lib32R
M32RINC = $(CC_ROOT)$/inc32R

MR32R_CONFG = $(MR32R_ROOT)$/m32rx$/bin$/cfg32r.exe
export LIB32R=$(MR32R_ROOT)$/m32rx$/lib32r

CC = $(M32RBIN)$/cc32R

AS = $(M32RBIN)$/as32R

AR = $(M32RBIN)$/lib32R

LD = $(M32RBIN)$/lnk32R


# I - macro for compiler option to define standard include paths (<>)
#
I = -I


# INCS_STD - C standard header search paths that can be added to INCS
# NOTE:  The standard m32r location for headers is automatically searched,
# after all other include paths. INCS_STD has no value.
#
INCS_STD =

# INCS = include paths, initially the standard headers but can be redefined or extended
#
INCS += \
  $(INCS_STD)

# ASINCS - assembler include paths
#
ASINCS = $(INCS)


# MOT_FROM_EXE_COMMANDS - commands to make motorola hex file
# from a .abs
#
define MOT_FROM_EXE_COMMANDS
   $(M32RBIN)$/lmc32R -o $@ $<
endef

# ELF_FROM_EXE_COMMANDS - commands to make elf file from .abs
#
define ELF_FROM_EXE_COMMANDS
   $(M32RBIN)$/conv32R -o $@ $<
endef


# AR_CREATE_COMMANDS - commands to create library $@ from $^
#
define AR_CREATE_COMMANDS
-$(RM) $@
@$(ECHO) ... library contains
@$(ECHO) ...  $(words $^)
@$(ECHO) ... modules
$(AR) -c .$/$@  $(wordlist 1,250,$^)
$(AR) -m .$/$@  $(wordlist 251,500,$^)
$(AR) -m .$/$@  $(wordlist 501,1000,$^)
@$(ECHO) ... created $@$(ECHOEND)
endef


# AR_UPDATE_COMMANDS - commands to replace $^ in library $@
#
define AR_UPDATE_COMMANDS
$(AR) -r $@ $^
@$(ECHO) ... updated $@$(ECHOEND)
endef


# AR_AGGREATE - Rules to create aggregate library ^@ from
# prerequisite libraries $^.
# The librarian does not allow to create an aggregate library.

define AR_AGGREGATE
@$(ECHO) aggegrate libraries not supported $(ECHOEND)
   
endef

