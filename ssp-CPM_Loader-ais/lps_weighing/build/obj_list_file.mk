
#############################################################################
# Objects
#############################################################################


# The OBJECTS variable specifies a list of object files that should be
# build and linked with the a32 or elf file. Object files that should not
# be re-build can be added to the LIBRARIES variable.

OBJECTS += \
	LpsUtility.o \
	LpsProcess.o \
	LpsInit.o \
	LpsUpdate.o \
	LpsWeighDumpState.o \
	LpsWeighDigDetect.o \
	LpsWeighDumpWtChange.o \
	LpsWeighBestBktWt.o \
	LpsWeighLlw.o \
	LpsWeighRangeWeigh.o \
	LpsZeroing.o \
	LpsWeighLiveWeigh.o \
	