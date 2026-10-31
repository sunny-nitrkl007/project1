########################################################################
# environment/makefiles/defs.mk                         clearmake -C gnu
########################################################################



########################################
# determine build type
########################################
ifndef BUILDING_OBJS
BUILDING_TGT_ARCH = TRUE
else
THISDIR := $(notdir $(CURDIR))
endif

########################################
# building anything
########################################

SRC_ROOT ?= $(REL_ROOT)$/src

########################################
# building target architecture
########################################
ifdef BUILDING_TGT_ARCH

VOB_ROOT = $(VOB_ROOT_T)
REL_ROOT = $(REL_ROOT_T)
LIBDIRS ?= $(addprefix _lib$/,$(notdir $(wildcard $(SRC_ROOT)$/lib$/*)))
APPDIRS ?= $(addprefix _app$/,$(notdir $(wildcard $(SRC_ROOT)$/app$/*)))

# MK_DIR2 - General shared makefiles
MK_DIR2 := $(ENV_ROOT)$/makefiles

endif


########################################
# building lib
########################################
ifdef BUILDING_LIB

VOB_ROOT = $(VOB_ROOT_L)
REL_ROOT = $(REL_ROOT_L)

LIB_NAME ?= lib$(THISDIR).a
LIB_DIR ?= ..
SRC_DIR ?= $(SRC_ROOT)$/lib$/$(THISDIR)

endif


########################################
# building app
########################################
ifdef BUILDING_APP

VOB_ROOT = $(VOB_ROOT_L)
REL_ROOT = $(REL_ROOT_L)

SRC_DIR ?= $(SRC_ROOT)$/app$/$(THISDIR)

_EXES = $(patsubst %.$(LCF_SUFFIX),%.$(EXE_SUFFIX),$(notdir $(wildcard $(SRC_DIR)$/*.$(LCF_SUFFIX))))
_FLSS = $(patsubst %.opt,%.fls,$(notdir $(wildcard $(SRC_DIR)$/*.opt)))

# Filter out OS specific applications that are not supported on tgt's (compiler/CPU)
# %_ose application names only built for tgt_diab_4.4a_PPC555EH
#
ifeq ($(findstring tgt_diab_4.4a_PPC555EH, $(TGT_ARCH)), tgt_diab_4.4a_PPC555EH)
EXES = $(_EXES)
FLSS = $(_FLSS)
endif

ifeq ($(findstring tgt_diab_4.2b_PPC555EH, $(TGT_ARCH)), tgt_diab_4.2b_PPC555EH)
# pOSEK application don't use a suffix.
# Build all applications without a suffix.
EXES = $(filter-out %_ose.$(EXE_SUFFIX) \
                    %_ose_ram.$(EXE_SUFFIX) \
                    %_osee.$(EXE_SUFFIX) \
                    %_osee_ram.$(EXE_SUFFIX) \
                    %_mr32r.$(EXE_SUFFIX), $(_EXES))
FLSS = $(filter-out %_ose.fls %_osee.fls, $(_FLSS))
endif

ifeq ($(TGT_ARCH), tgt_rvct_2.1_ARM7TDMI)
# Build only "%_osee." applications.
EXES = $(filter %_osee.$(EXE_SUFFIX), $(_EXES))
FLSS = $(filter %_osee.fls, $(_FLSS))
endif

ifeq ($(findstring tgt_diab_4.2b_PPC555EHST, $(TGT_ARCH)), tgt_diab_4.2b_PPC555EHST)
# Filter out the OSE and OSEE applications for PPC STOS applications.
EXES = $(filter-out %_ose.$(EXE_SUFFIX) %_osee.$(EXE_SUFFIX) , $(_EXES))
FLSS = $(filter-out %_ose.fls %_osee.fls, $(_FLSS))
endif

ifeq ($(findstring tgt_cc32r_4.20r1_M32Rx, $(TGT_ARCH)), tgt_cc32r_4.20r1_M32Rx)
# Filter out the OSE and OSEE applications for MR32 applications.
EXES = $(filter-out %_ose.$(EXE_SUFFIX) %_osee.$(EXE_SUFFIX) , $(_EXES))
FLSS = $(filter-out %_ose.fls %_osee.fls, $(_FLSS))
endif

ifeq ($(findstring tgt_cc32r_4.30_M32Rx, $(TGT_ARCH)), tgt_cc32r_4.30_M32Rx)
# Filter out the OSE and OSEE applications for MR32 applications.
EXES = $(filter-out %_ose.$(EXE_SUFFIX) %_osee.$(EXE_SUFFIX) , $(_EXES))
FLSS = $(filter-out %_ose.fls %_osee.fls, $(_FLSS))
endif

LDOBJS = $(OBJS)

ifeq ($(OS),Windows_NT)
HCONV = $(VOB_ROOT)$/dev_tools$/hfile$/hfile_gen$/pc$/exe$/hfilegen.exe
endif

ifeq ($(OS),unix)
HCONV = $(VOB_ROOT)$/dev_tools$/hfile$/hfile_gen$/unix$/exe$/hfilegen.exe
endif


endif


########################################
# building lib or app
########################################
ifdef BUILDING_OBJS

OSEE_ROOT = $(ENV_ROOT)$/OSEE$/epsilon$/arm$/krn375
OSE_ROOT = $(ENV_ROOT)$/OSE$/OSE4.4.2
OSEK_ROOT = $(ENV_ROOT)$/isi$/posek_30.1
OEL_ROOT = $(VOB_ROOT)$/lib_oel$/oel
HAL_ROOT = $(VOB_ROOT)$/lib_a4$/hal
SCL_ROOT = $(VOB_ROOT)$/lib_a4$/scl
MR32R_ROOT = $(ENV_ROOT)$/mitsubishi$/mr32r_3.50r2

OSEE_CONFARM = $(OSEE_ROOT)$/bin$/confarm.exe
OSEE_CONFARM_GNU_PATCH = $(ENV_ROOT)$/customization$/osee$/osee.S.patch

OR = oilreader
#OR = $(OSEK_ROOT)$/bin$/oilreader
ORFLAGS=


# Tool for fixing a stack bug in pOSEK 3.0.1
PSF_ROOT = $(VOB_ROOT)$/dev_tools$/pOsek
PSF = $(PSF_ROOT)$/posek_301_stack_fix.exe


SRC_EXTS = c cc cpp s oil
_OBJS = $(foreach ext, $(SRC_EXTS), \
   $(patsubst %.$(ext),%.o,$(notdir $(wildcard $(SRC_DIR)$/*.$(ext)))))



COMPILE.c = $(CC) $(CFLAGS) $(CDEFS) $(INCS) -c

COMPILE.cc = $(CXX) $(CXXFLAGS) $(CDEFS) $(INCS) -c

COMPILE.s = $(AS) $(ASFLAGS) $(ASDEFS) $(ASINCS)

LINK = $(LD) $(LD_MF) $(LDFLAGS) $(LIB_DIRS)



INCS_OSEK_KRN = \
  $(I)$(OSEK_ROOT)$/include

INCS_OSEK = \
  $(I)$(OEL_ROOT)$/include_osek \
  $(I)$(OSEK_ROOT)$/include

# *rvct* targets use osee ads/include
ifneq (,$(findstring rvct, $(TGT_ARCH)))
   INCS_OSEE = \
     $(I)$(OEL_ROOT)$/include_osee \
     $(I)$(OSEE_ROOT)$/ads$/include
# *gcc* targets use osee gnu/include
else
ifneq (,$(findstring gcc, $(TGT_ARCH)))
   INCS_OSEE = \
     $(I)$(OEL_ROOT)$/include_osee \
     $(I)$(OSEE_ROOT)$/gnu$/include
endif
endif

INCS_OELUK = \
  $(I)$(OEL_ROOT)$/include_oeluk

ifeq ($(findstring _PPC5, $(TGT_ARCH)), _PPC5)
INCS_OSE = \
  $(I)$(OEL_ROOT)$/include_ose \
  $(I)$(OSE_ROOT)$/powerpc$/include \
  $(I)$(OSE_ROOT)$/powerpc$/krn-5xx$/include
else
ifeq ($(findstring _WIN32, $(TGT_ARCH)), _WIN32)
INCS_OSE = \
  $(I)$(OEL_ROOT)$/include_ose \
  $(I)$(OSE_ROOT)$/sfk-win32$/include \
  $(I)$(OSE_ROOT)$/sfk-win32$/krn-win32$/include
endif
endif

INCS_MR32R = \
  $(I)$(OEL_ROOT)$/include_mr32r \
  $(I)$(MR32R_ROOT)$/m32rx$/inc32r \
  $(I)$(MR32R_ROOT)$/m32rx$/lib32r

%_ose.o: INCS+=$(INCS_OSE)

%_osee.o: INCS+=$(INCS_OSEE)

%_osek.o: INCS+=$(INCS_OSEK)

%_mr32r.o: INCS+=$(INCS_MR32R)

%_oeluk.o: INCS+=$(INCS_OELUK)

# SRC_DIR_OSE - The source directory for the ose dmake portion of the build.
# Default is current object directory so app source is directly
# built by clearmake.  App def.mk can define as $(SRC_DIR) to have dmake
# build the app src.
#
SRC_DIR_OSE = .


endif





