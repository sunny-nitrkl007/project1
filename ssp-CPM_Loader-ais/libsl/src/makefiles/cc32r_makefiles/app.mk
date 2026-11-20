########################################################################
# environment/makefiles/app.mk
########################################################################

# BUILDING_OBJS and BUILDING_APP must be defined to build a app.
#
BUILDING_OBJS =	TRUE
BUILDING_APP = TRUE

# Define SRC_DIR here to override the standard structure.
# Do NOT define to use these scripts across components and targets.
#
#SRC_DIR = .
#LIB_DIR = .
#LIB_NAME = 


# include common script for this target architecture
# NOTE:  $/ is not yet defined but / will work here
#
include ../../Makefile
