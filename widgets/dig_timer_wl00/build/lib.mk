#******************************************************************************
# COPYRIGHT (C) 2019 CATERPILLAR INC.   ALL RIGHTS RESERVED.
#
# FILE:
#   lib.mk
#
# DESCRIPTION:
#   Makefile shared by all targets to set common information based on the target.
#
#******************************************************************************

#Before this file is included $(TARGET_NAME) must be defined.
# and optionally the default build target should be specified.
#After this file is included the appropriate common make file must be included

#############################################################################
# Project Configuration

# specifies the name of the folder this library is in
APP_FOLDER_NAME = dig_timer_wl00

# Specifies the name of the .a32, .x, .csa, and .fls file.
APP_NAME_SHORT  = $(APP_FOLDER_NAME)
APP_NAME        = lib_$(APP_NAME_SHORT)

#Location To Move Archive File To After Build Completed
A32DIR = ../../$(APP_FOLDER_NAME)-a/$(TARGET_NAME)

# Specifies the location of the VIEW root directory. (VOB_ROOT due to legacy mistake)
# If possible, use a relative path (../../..), so that people can build
# through their M: drive and logical drives. Omit the trailing slash ('/').
VOB_ROOT = ../../..

# DODIR - Defines the path for all derived objects. The path is relative to the
# location of the makefile. Omit the trailing slash ('/').
DODIR = do_$(TARGET_NAME)

#############################################################################

#############################################################################
# Makelets
VPATH += ../src

MAKES_INC += includes_$(TARGET_NAME).mk
MAKES_INC += objects.mk


#############################################################################

