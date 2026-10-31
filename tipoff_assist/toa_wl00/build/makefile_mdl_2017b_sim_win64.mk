#******************************************************************************
# COPYRIGHT (C) 2019 CATERPILLAR INC.   ALL RIGHTS RESERVED.
#
# FILE:
#   makefile_mdl_2017b_sim_win64.mk
#
# DESCRIPTION:
#   Makefile for a given target.
#******************************************************************************


# Specifies the location of the VIEW root directory. (VOB_ROOT due to legacy mistake)
# If possible, use a relative path (../../..), so that people can build
# through their M: drive and logical drives. Omit the trailing slash ('/').
VOB_ROOT = ../../..


#############################################################################
# Targets

# Generate CodeGen (*.c; *.h). Rebuild the Simulink Model
mdl : codegen_build 

# Build library *.a
lib: WIN64_LIB

# Build 'shared object' library, dll
dll: WIN64_DLL_TGT_ONLY REL_DLL

# Build all of the above targets
all: clean mdl lib dll

#############################################################################
# Target Configuration
TARGET_NAME    = tgt_gcc_4.8.2_sim_win64

#############################################################################
# DODIR - Defines the path for all derived objects. The path is relative to the
# location of the makefile. Omit the trailing slash ('/').
DODIR = do_$(TARGET_NAME)

#############################################################################
#Location To Move Archive File To After Build Completed
A32DIR = ../../cs_mtp00-a/$(TARGET_NAME)
# Destination for dll file... 
DEST_PATH = ..\..\cs_mtp00-a\$(TARGET_NAME)

#############################################################################
# Path to BuilDescription 
BD = ../pkg/$(APP_NAME_SHORT).buildescription

#############################################################################
# Build Model Target (generate *.c and *.h files)
#############################################################################
codegen_build:
	@echo "Generating MATLAB Derived Objects"
	$(VOB_ROOT)\lib_autocode\CATutils_MatLab\toolbox\makefile_build\model_build.exe \
	-buildescription $(BD) -mathworks_release R2017b -matlab_arch win64
	@echo 
	@echo "Done Generating MATLAB Derived Objects"
	@echo 
	
#############################################################################
# Makelets
MAKES_INC += includes.mk
MAKES_INC += objects.mk	
	
#############################################################################
# Makefiles Includes
include $(VOB_ROOT)/lib_machine/tools/makefile/makefile_sim_win64.mk
#############################################################################