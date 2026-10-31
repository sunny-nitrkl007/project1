########################################################################
# defs.mk                                               clearmake -C gnu
# Customize this file to build your application. 
# Common_defs.mk file includes the common build rule.
# Follow the instructions given in comments to make changes in this file.
########################################################################

########################################################################
# APP_NAME - specify the application name here
########################################################################

APP_NAME = test_sss_sample_app
 
########################################################################
# Conditional build options like
# "Do not build this application for the STOS targets."
# ifeq ($(TGT_ARCH), tgt_diab_4.2b_PPC555EHST)
# EXES = 
# FLSS = 
# endif
########################################################################

SSS-A_ROOT = $(VOB_ROOT)$/lib_sss$/sss-a

ifeq ($(findstring tgt_diab_5.8.0.0_PPCVLEEF, $(TGT_ARCH)), tgt_diab_5.8.0.0_PPCVLEEF)
INCS += $(I)$(HAL_ROOT)$/include_r
INCS += $(I)$(HAL_ROOT)$/include_r$/freescale$/mpc55xx
INCS += $(I)$(SCL_ROOT)$/include
INCS += $(I)$(LIB_SSS)$/include
endif

ifeq ($(findstring tgt_ar_diab_5.9.4.0_PPCVLEEF, $(TGT_ARCH)), tgt_ar_diab_5.9.4.0_PPCVLEEF)
EXES = $(filter %_ar_a6p1_rtaos.$(EXE_SUFFIX), $(_EXES))
FLSS = $(filter %_ar_a6p1_rtaos.fls, $(_FLSS))
INCS += $(I)$(VOB_ROOT)$/lib_oel$/oel_os_cfg$/include
INCS += $(I)$(VOB_ROOT)$/lib_oel$/oel_os_cfg_csns_test$/include
INCS += $(I)$(VOB_ROOT)$/lib_oel$/oel$/include_ar
INCS += $(I)$(VOB_ROOT)$/lib_hal_a6p1/lib_a4$/hal$/include
INCS += $(I)$(LIB_SSS)$/include
LIB_DIRS += \
   -L $(OEL-A_ROOT)$/$(TGT_ARCH)$/lib \
   -L $(CD-A_ROOT)$/$(TGT_ARCH)$/lib \
   -L $(SCL-A_ROOT)$/$(TGT_ARCH)$/lib \
   -L $(VOB_ROOT)$/lib_oel$/oel_os_cfg-a$/$(TGT_ARCH)$/lib \
   -L $(VOB_ROOT)$/lib_oel$/oel_os_cfg_csns_test-a$/$(TGT_ARCH)$/lib  \
   -L $(SSS-A_ROOT)$/$(TGT_ARCH)$/lib 
   
endif

########################################################################
# Use Hardware Floating Point
# (uncomment to use floating point)
########################################################################
#CTARGET = $(CTARGET_HWFP)

########################################################################
# CDEFS - Compilation macros for Application specific Files
########################################################################
 app_can_init_a5m4i1.o: CDEFS += -DA5M4I1
 app_can_init_a6p1.o: CDEFS += -DA6P1


########################################################################
# Common Objects to exclude from compilation
# Here include the application specific filter-out files other than the 
# common files(oil, app_inits, app_can_init, app_rtos_config_osxx, etc.)
# OBJS_APP_COMMON_EXCLUDE = $(_OBJS) if all other files have to be compiled.
# OBJS_APP_COMMON_EXCLUDE = $(filter-out xxxx.o yyyy.o ...,$(_OBJS) )
########################################################################
OBJS_APP_COMMON_EXCLUDE := $(filter-out     \
                               app_can_init.o                  \
                               app_hal_canv3_init.o             \
                               app_hal_canv3_test.o \
                               oil.o                           \
                               app_inits.o                     \
							   app_ar_a6p1_task_config.o   \
							   app_rtos_config_oeluk.o   \
                               task_set_01_global.o,$(_OBJS))

########################################################################
# Additional Application Sepcific Objects for TCP IP CLIENT A5M4I1
########################################################################    
OBJS_APP_A5M4I1 :=  app_can_init_a5m4i1.o        \
                    task_set_01_global_a5m4i1.o   
                                         
########################################################################
# Additional Application Sepcific Objects for TCP IP CLIENT A5M4I1
########################################################################    
OBJS_APP_A6P1 := \
               app_can_init_a6p1.o                     \
			   app_ar_a6p1_task_config_a6p1.o        \
			   app_inits_a6p1.o        \
			   task_set_01_global_a6p1.o

########################################################################
# LIB_DIRS - directories to search for libraries
# Application specific Library Files
# Add only the additional application specific library options here. 
# common_defs.mk provides includes basic libraries
########################################################################

%.elf: LIB_DIRS += \
   -L $(VOB_ROOT)$/lib_hal_a6p1$/lib_a4$/hal-a$/$(TGT_ARCH)$/lib  \
   -L $(VOB_ROOT)$/lib_hal_a6p1$/lib_a4$/hal_common-a$/$(TGT_ARCH)$/lib \
   -L $(VOB_ROOT)$/lib_hal_a6p1$/lib_a4$/hal_e200zx-a$/$(TGT_ARCH)$/lib       
                                       
########################################################################
# Additional Application Sepcific Objects for TCP IP CLIENT A5M4I1
########################################################################    

########################################################################
# LIB_DIRS - directories to search for libraries
# Application specific Library Files
# Add only the additional application specific library options here. 
# common_defs.mk provides includes basic libraries
########################################################################
LIB_DIRS += \
  -L$(SCL_ROOT)$/$(TGT_ARCH)$/lib \
  -L$(CD_ROOT)$/$(subst _dbg,,$(TGT_ARCH))$/lib 
                                         
########################################################################
# define the object files.
# Add or remove the platforms you want to build.
########################################################################
ifeq ($(findstring tgt_diab_5.8.0.0_PPCVLEEF, $(TGT_ARCH)), tgt_diab_5.8.0.0_PPCVLEEF)
OBJS = \
  $(OBJS_COMMON)        \
  $(OBJS_A5M4I1)    
  
endif

########################################################################
# define the object files.
# Add or remove the platforms you want to build.
########################################################################

ifeq ($(findstring tgt_ar_diab_5.9.4.0_PPCVLEEF, $(TGT_ARCH)), tgt_ar_diab_5.9.4.0_PPCVLEEF)
OBJS = \
   $(OBJS_APP_COMMON_EXCLUDE) \
   $(OBJS_APP_A6P1)
endif

########################################################################
#
# LIB_DIRS - directories to search for libraries
#
########################################################################  

ifeq ($(findstring tgt_diab_5.8.0.0_PPCVLEEF, $(TGT_ARCH)), tgt_diab_5.8.0.0_PPCVLEEF)

LIB_DIRS += \
  -L$(SSS-A_ROOT)$/$(TGT_ARCH)$/lib \
  -L$ \lib_oel\oel\tgt_diab_5.8.0.0_PPCVLEEF\lib 
endif

########################################################################
# Include the common part of defs.mk
########################################################################
ifeq ($(findstring tgt_diab_5.8.0.0_PPCVLEEF, $(TGT_ARCH)), tgt_diab_5.8.0.0_PPCVLEEF)
include $(VOB_ROOT)/lib_a4/scl/src/common/common_defs.mk
endif

########################################################################
#
# LIBS - libraries for linking (Notes 1) - WindRiver targets
#
########################################################################
$(APP_NAME)_a5m4i1_oeluk.elf: LIBS += \
-lsss 
   
########################################################################
#
# LIBS - libraries for linking (Notes 1) - WindRiver targets
#
########################################################################
ifeq ($(findstring tgt_ar_diab_5.9.4.0_PPCVLEEF, $(TGT_ARCH)), tgt_ar_diab_5.9.4.0_PPCVLEEF)

$(APP_NAME)_ar_a6p1_rtaos.elf: LIBS += \
   -lhal_a6p1  \
   -loel_ar_bt_mpc5777C  \
   -loel_memmap   \
   -lc \
   -lscl \
   -loel_os_cfg_csns_test_a6p1_bt \
   -lhal_canv3  \
   -loel_rtos_ar_et \
   -lsss   
endif

