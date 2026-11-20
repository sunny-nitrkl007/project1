########################################################################
# environment/makefiles/tools_Windows_NT.mk             clearmake -C gnu
########################################################################

ifneq ($(OS),Windows_NT)
include OS_is_$(OS)_but_initially_built_with_Windows_NT
endif


# SHELL
#
# OSE applications use OSE dmake scripts that require the DOS shell. 
# If the environment variable SHELL is not defined, then dmake reads
# startup script $(MAKECMD:d)startup/startup.mk which includes script
# $(MAKECMD:d)startup/windows_NT/macros.mk which defines SHELL equal to
# environment variable COMSPEC, which is the full path to the DOS shell
# (C:\WINNT\system32\cmd.exe on my PC).  Some user's define SHELL and
# the build will fail if it has any other value.  This gnu make script
# can redefine SHELL but not unexport it.  Therefore it is here defined
# as expected by OSE dmake.  It must be the full path.  dmake hangs if
# defined as cmd.exe.
#
# If invoked from a bash shell, environment variables are converted to
# upper case.  I am not aware of a case insensitive method to match it
# so both ComSpec and COMSPEC are checked.  No error is reported here
# if neither is defined but OSE dmake will likely fail.
#
ifneq ($(ComSpec),)
export SHELL := $(ComSpec)
else
ifneq ($(COMSPEC),)
export SHELL := $(COMSPEC)
else
endif
endif


# / - Macro for host independent path separator
# It is set to \ on this host
# This is done in 2 steps to avoid interpreting a trailing \ as
# line continuation.  The x is appended then stripped.
# Clearmake on Windows will use \ in generated paths.
# If all tools support the unix / then this can defined as / and
# the CMAKE_PNAME_SEP will be defined to change the generated
# separators.
/ := \x
/ := $(/:%x=%)
ifeq ($/,/)
CMAKE_PNAME_SEP = $/
endif

ECHO = echo.
ECHOEND =
ECHOEMPTY = echo.
DOLLAR = $$
QUOTE = "

CAT = copy
CAT_SEPARATOR = +
CAT_OUT_PREFIX =

# the /D is required to accept drive letters.
CD = chdir /D
CP = copy
MV = rename
RM = del /q
MKDIR = mkdir
RMDIR = rmdir /s /q


