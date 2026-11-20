############# Target type (Debug/Release) ##################
############################################################
ifeq ($(CPU),)
CPU=32
endif

UNITTEST_TARGET_NAME=gcovTest

THE_PATH = $PATH
CFLAGS=-O0 -g -std=c++11 -Wall -Wmissing-declarations -Wredundant-decls -Wshadow -Wlogical-op -Wcast-align -Woverloaded-virtual -Werror-implicit-function-declaration #-Wundef
 
LinkDebug=-g
LinkRelease=-O -s
SUPPRESS_WARNINGS=-Wno-write-strings -Wno-builtin-macro-redefined
COMMON_DEFINES = -DA5N2 -DLINUX_SYSTEM
C___DEFINES =
CPP_DEFINES = -DUSE_IOSTREAM -DOM_NO_TEMPLATES_USAGE -DOM_NO_FRAMEWORK_MEMORY_MANAGER
CPP_GCOV=-fprofile-arcs -ftest-coverage
LINK_GCOV=-lgcov -coverage
ConfigurationCPPCompileSwitches= $(SUPPRESS_WARNINGS) $(COMMON_DEFINES) $(CPP_DEFINES) $(INCLUDE_PATH) $(CFLAGS) $(CPP_GCOV) -c
ConfigurationCCompileSwitches=   $(SUPPRESS_WARNINGS) $(COMMON_DEFINES) $(C___DEFINES) $(INCLUDE_PATH) $(CFLAGS) $(CPP_GCOV) -c



###### Commands & Flags ################
RM=/bin/rm -rf
MD=/bin/mkdir -p
CC=g++
LIB_CMD=arm-linux-ar
LINK_CMD=$(CC)
LIB_FLAGS=rvu

####### Context macros ##################

TGT_A5N2=tgt_gcc_4.8.0_a5n2
TGT_ARMNIX=tgt_gcc_4.8.0_arm11_linux
TGT_X86=tgt_gcc_4.4.3_x86_linux

BUILD_ROOT=../../../../
all : $(UNITTEST_TARGET_NAME)

INCLUDE_PATH= \
  -I. \
  -I ../../include \
  -I$(BUILD_ROOT)GTest \
  -I$(BUILD_ROOT)GTest/include \
  -I$(BUILD_ROOT)lps_app_common/include \
  -I$(BUILD_ROOT)lps_common/include \
  -I ../../../lps_weighing_interface/include \
  -I ../../include \
  -I$(BUILD_ROOT)../MAAL-a/inc \



LIB_DIRS = \
	-L. \
	-L../../../../GTest \
	-L$(BUILD_ROOT)../MAAL-a/x86_libs \



LIBS = -Wl,--start-group \
	-pthread -lstdc++ -lm\
	-lCPMFilters \
	-lgtest\
-Wl,--end-group  

C_SRCS = $(wildcard *.c)
CC_SRCS = $(wildcard *.cc) 

C_OBJS = $(patsubst %.c,%.o,$(C_SRCS))
CC_OBJS = $(patsubst %.cc,%.o,$(CC_SRCS))



#####################################################################
##################### Context dependencies and commands #############

.c.o:
	@echo Compiling $<
	$(CC) $(ConfigurationCCompileSwitches) $< -o $@

.cc.o:
	@echo Compiling $<
	@echo $(value THE_PATH)
	$(CC) $(ConfigurationCPPCompileSwitches) $< -o $@

####################################################################################
#        Predefined linking instructions       #
####################################################################################
$(UNITTEST_TARGET_NAME): $(CC_OBJS) $(C_OBJS) 
	@echo Linking $(UNITTEST_TARGET_NAME)
	@echo $(LINK_CMD) $(CC_OBJS) $(C_OBJS) $(LIB_DIRS) $(LIBS) $(LinkDebug) $(LINK_GCOV)  -o $(UNITTEST_TARGET_NAME)
	@$(LINK_CMD) $(CC_OBJS) $(C_OBJS) $(LIB_DIRS) $(LIBS) $(LinkDebug) $(LINK_GCOV)  -o $(UNITTEST_TARGET_NAME)
	

cleanGtest:
	@echo cleanGtest
	$(RM) $(wildcard html)
	$(RM) $(wildcard *.xml)
	$(RM) $(C_OBJS)
	$(RM) $(CC_OBJS)
	$(RM) $(UNITTEST_TARGET_NAME)
	$(RM) $(wildcard *.gcno)
	$(RM) $(wildcard *.gcda)
	
clean:
	@echo clean
	$(RM) $(C_OBJS)
	$(RM) $(CC_OBJS)
	$(RM) $(UNITTEST_TARGET_NAME)
	$(RM) $(wildcard *.gcno)
	$(RM) $(wildcard *.gcda)
	$(RM) $(wildcard coverage.xml)
	
cleanGcno:
	@echo cleanupGCNOfiles
	$(RM) $(wildcard gtest*.gcno)
	$(RM) $(wildcard gtest*.gcda)
	$(RM) $(wildcard *_unittest.gcda)
	$(RM) $(wildcard *_unittest.gcno)
