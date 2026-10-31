########################################################################
# environment/makefiles/target.mk				        clearmake -C gnu
########################################################################

# This is the first of several common environment/makefiles and
# specific release build/makefiles that are concatenated to create
# a top level tgt_*/Makefile.  For consistency this tgt_*/Makefile is
# used for all builds throughout the target architecture.  It is
# directly used to manage a recursive build of the entire target and
# is included in each lib and app Makefile to manage the build of each
# of these.  It supports three contexts: BUILDING_TGT_ARCH,
# BUILDING_LIB, and BUILDING_APP.  In BUILDING_LIB and BUILDING_APP
# make is invoked in a individual tgt_*/lib/* or tgt_*/app/* directory.
# These contain a tgt_*/lib/*/Makefile that defines the release root
# relative to that directory and includes this Makefile.  A lib or app
# build is implied by the lib or app parent directory name. In
# BUILDING_TGT_ARCH, make is invoked in the trg_% directoy and directly
# uses this tgt_%/Makefile.  This is implied by the lack of a definition
# for REL_ROOT.
#
# For efficiency, this file is generated once rather than including all
# of its constituents with each invocation of make. 

# OS - define the host operating system
# Windows NT and 2000 define OS = Windows_NT.
# Default to unix if undefined.
#
OS ?= unix

# default - This first rule is the default if no targets are specified
#
help:

