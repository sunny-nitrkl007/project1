
#############################################################################
# Objects
#############################################################################


# The OBJECTS variable specifies a list of object files that should be
# build and linked with the a32 or elf file. Object files that should not
# be re-build can be added to the LIBRARIES variable.

OBJECTS += LpsCalInit.o
OBJECTS += LpsCalUpdate.o
OBJECTS += LpsCal.o
OBJECTS += LpsCalMain.o
OBJECTS += LpsCalUtility.o
OBJECTS += LpsCalAppInterface.o


