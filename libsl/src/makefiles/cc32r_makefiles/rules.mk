########################################################################
# environment/makefiles/rules.mk                        clearmake -C gnu
########################################################################
 
help:

# The following causes -p to omit most of its output
#.PRECIOUS: all targets libs apps clean
#.PHONY: libs apps all tree clean

# MUST clear suffixes to avoid the builtin rules.
# It appears to ignore case on Windows and attempts to
# make a .s from a .S(uses .s).  This fails if .s is
# checked in.  It might overwrite it if not!!!!!!!!!
.SUFFIXES:


########################################
# building target architecture
########################################
ifdef BUILDING_TGT_ARCH

all: libs apps

libs: $(LIBDIRS)

# if tree is not a goal, libs will make aggregate libs
#
ifeq (,$(findstring tree, $(MAKECMDGOALS)))
libs: $(AGGREGATE_LIBS)	
endif

apps: $(APPDIRS)

tree: all ;

# ensure libs built before any app
#
$(APPDIRS): libs

$(LIBDIRS) $(APPDIRS): _%: app lib % %$/Makefile %$/Makefile.options
ifeq (,$(findstring tree, $(MAKECMDGOALS)))
	$(CD) $(patsubst _%,%,$@) && "$(MAKE)" all
endif

aggregate_libs: $(AGGREGATE_LIBS)

$(AGGREGATE_LIBS):
	$(AR_AGGREGATE)


# app app/* lib lib/* - rules to create these directories
#	
lib app $(patsubst _%,%,$(LIBDIRS) $(APPDIRS)):
	-$(MKDIR) $@ 


# app/Makefile - This will create app/*/Makefile
#
$(patsubst _%,%$/Makefile,$(APPDIRS)):  $(MK_DIR2)$/app.mk
	$(CP) $< $@


# lib/Makefile - This will create lib/*/Makefile
#
$(patsubst _%,%$/Makefile,$(LIBDIRS)):  $(MK_DIR2)$/lib.mk
	$(CP) $< $@


# Makefile.options - This will create Makefile.options
#
%$/Makefile.options:  Makefile.options
	$(CP) $< $@

# help - provide help
#
help:
	@$(ECHO)Targets:$(ECHOEND) 
	@$(ECHO)  all - libs and apps for this target architectures$(ECHOEND) 
	@$(ECHO)  libs - build all libs$(ECHOEND) 
	@$(ECHO)  aggregate_libs - build only aggregate libs$(ECHOEND) 
	@$(ECHO)  apps - build all apps and libs$(ECHOEND) 
	@$(ECHO)  tree - create target directory tree without building$(ECHOEND) 
	@$(ECHO)Options:$(ECHOEND) 
	@$(ECHO)  APPDIRS=$(QUOTE)_[path] ...$(QUOTE) - specific apps, [path] is relative to SRC_ROOT$(ECHOEND) 
	@$(ECHO)  LIBDIRS=$(QUOTE)_[path] ...$(QUOTE) - specific libs, [path] is relative to SRC_ROOT$(ECHOEND) 
	@$(ECHO)Values:$(ECHOEND) 
	@$(ECHO)  APPDIRS=$(APPDIRS)$(ECHOEND) 
	@$(ECHO)  LIBDIRS=$(LIBDIRS)$(ECHOEND) 
	@$(ECHOEMPTY)

endif


########################################
# building lib
########################################
ifdef BUILDING_LIB

all: lib ;

lib: $(LIB_DIR)$/$(LIB_NAME)

ifdef ARCHIVE_FROM_ALL_O_FILES
$(LIB_DIR)$/$(LIB_NAME): $(OBJS)
	$(AR_ALL_O_CREATE_COMMANDS)
else
$(LIB_DIR)$/$(LIB_NAME): $(OBJS)
	$(AR_CREATE_COMMANDS)
endif

# help - provide help
#
help:
	@$(ECHO)Targets:$(ECHOEND) 
	@$(ECHO)  all - lib$(ECHOEND) 
	@$(ECHO)  lib - build all objects and library$(ECHOEND) 
	@$(ECHO)  $(OBJS) - specific object$(ECHOEND) 
	@$(ECHOEMPTY)

endif


########################################
# building app
########################################
ifdef BUILDING_APP

all: app ;

app: exes flss

exes: $(EXES)

flss: $(FLSS)

# %.o %.h %.$(LCF_SUFFIX) from %.oil
#
# oil.c includes oil.h and compile must precede renaming it.
# The .c file is renamed to avoid using a .c from
# another oil file or other version of the same oil file.
# The source can be named oil.oil to get the normal oil.* files.
# There is a separate rule for oil.oil to avoid removing oil.h
# and attempting to rename it to oil.h.  The %.c is renamed
# %.c.intermediate to avoid using an outdated $.c or an oil.c
# from a different %.oil file.
#
# Can not use %.o %.h %.dld: $(SRC_DIR)$/%.oil    NOTE-21
# The dependencies of %.h and %.dld are then specified as
# separate pattern rules with no commands and a dependency
# on the %.o which has commands to build them.
#
oil.o: $(SRC_DIR)$/oil.oil 
	@echo Invoking OIL Reader...
	@(set POSEK_SYS=$(OSEK_ROOT)$/sys$/ppc& \
	$(OR) $(ORFLAGS) $< )
	-@$(RM) oil.c.orig
	$(MV) oil.c oil.c.orig
	$(PSF) oil.c.orig -o oil.c
	$(CC) $(CFLAGS_OSEK_KRN) $(INCS_OSEK_KRN) $(TARGET_ARCH) -c \
	  -o oil.o	oil.c
	-@$(RM) oil.c.intermediate oil.$(LCF_SUFFIX)
	$(MV) oil.c oil.c.intermediate
	$(MV) oil.lk oil.$(LCF_SUFFIX)

%.o: $(SRC_DIR)$/%.oil 
	@echo Invoking OIL Reader...
	@(set POSEK_SYS=$(OSEK_ROOT)$/sys$/ppc& \
	$(OR) $(ORFLAGS) $< )
	-@$(RM) $*.c.orig
	$(MV) oil.c $*.c.orig
	$(PSF) $*.c.orig -o oil.c
	$(CC) $(CFLAGS_OSEK_KRN) $(INCS_OSEK_KRN) $(TARGET_ARCH) -c \
	  -o $*.o	oil.c
	-@$(RM) $*.c.intermediate $*.h $*.$(LCF_SUFFIX)
	$(MV) oil.c $*.c.intermediate
	$(MV) oil.lk $*.$(LCF_SUFFIX)
	$(MV) oil.h $*.h 

%.h: $(SRC_DIR)$/%.oil %.o ; 

%.$(LCF_SUFFIX): $(SRC_DIR)$/%.oil %.o ; 

# %_osee.o from %_osee.con for rvct
#
# The OSE Epsilon RTOS is a generated assembly file generated from the .con
# file in the source directory.
#

%_osee.S: $(SRC_DIR)$/%_osee.con
	$(OSEE_CONFARM) $< $@

%_osee.o: %_osee.S
	$(COMPILE.s) -o $@ $<


# %_osee_gcc.o from %_osee.con for gcc
#
# The OSE Epsilon RTOS is a generated assembly file generated from the .con
# file in the source directory.
#
# NOTE:  The generated file for gnu has a defect that prevents assembly.
#        This is fixed with GNU patch.  This requires build from a cygwin
#        window with tr and patch.  patch requires unix eol (not doccumented).
#        This rule requires an _osee_gnu.o suffix from a config with _osee.con.
#        The patch file is defined for a fixed file name of "osee.S".
#        This will convert a config file from rvct to gcc so a common config
#        file can be used.

%_osee_gcc.o: $(SRC_DIR)$/%_osee.con
	@echo ... Setting config for GNU
	sed -e /COMPILER/s/ARM/GNU/ $< > $*_osee.con
	@echo ... Generating OSEE kernel code
	$(OSEE_CONFARM) $*_osee.con $*_osee.unpatched
	@echo ... converting to unix eol before applying patch
	tr -d \r < $*_osee.unpatched > osee.S
	@echo ... patching
	patch -p1 < $(OSEE_CONFARM_GNU_PATCH) -o $*_osee.S
	$(COMPILE.c) -o $@ $*_osee.S



# %_ose.elf from %_ose.dld
#
# NOTE:  This must preceed more general %.$(EXE_SUFFIX) rule.
# Must explicitly delete the target to force a rebuild
# clearmake has already determined that it should be rebuilt
# but dmake is ignorant of library dependencies and will often
# fail to rebuild if it exists.
#
%_ose.$(EXE_SUFFIX): $(SRC_DIR)$/%_ose.$(LCF_SUFFIX) $(OBJS)
	-$(RM) $@
	$(OSE_ROOT)$/win32$/bin$/dmake -f $(SRC_DIR)$/makefile_ose.mk \
	  VOB_ROOT=$(VOB_ROOT) \
	  USERCONF=$(SRC_DIR)$/userconf_ose.mk \
	  OSEROOT=$(OSE_ROOT) \
	  COMPILER=$(OSE_COMPILER) \
	  COMPILERROOT=$(OSE_COMPILERROOT) \
	  TGT_ARCH=$(TGT_ARCH) \
	  OBJ=. \
	  SRC=$(SRC_DIR_OSE) \
	  EXECUTABLE_NAME=$*_ose \
	  EXECUTABLE_DIR=. \
	  "OBJECTS_FROM_APP=$(LDOBJS)" \
	  "LIBDIRS_FROM_APP=$(LIB_DIRS)" \
	  "LIBRARIES_FROM_APP=$(LIBS)" \
	  LCF=$< all

%_ose_ram.$(EXE_SUFFIX): $(SRC_DIR)$/%_ose_ram.$(LCF_SUFFIX) $(OBJS)
	-$(RM) $@
	$(OSE_ROOT)$/win32$/bin$/dmake -f $(SRC_DIR)$/makefile_ose.mk \
	  VOB_ROOT=$(VOB_ROOT) \
	  USERCONF=$(SRC_DIR)$/userconf_ose.mk \
	  OSEROOT=$(OSE_ROOT) \
	  COMPILER=$(OSE_COMPILER) \
	  COMPILERROOT=$(OSE_COMPILERROOT) \
	  TGT_ARCH=$(TGT_ARCH) \
	  OBJ=. \
	  SRC=$(SRC_DIR_OSE) \
	  EXECUTABLE_NAME=$*_ose_ram \
	  EXECUTABLE_DIR=. \
	  "OBJECTS_FROM_APP=$(LDOBJS)" \
	  "LIBDIRS_FROM_APP=$(LIB_DIRS)" \
	  "LIBRARIES_FROM_APP=$(LIBS)" \
	  LCF=$< all

# %.$(EXE_SUFFIX) from $(SRC_DIR)$/%.$(LCF_SUFFIX)
#


ifdef LD_FROM_FILE
# Link using a text file for the command line options.
ifdef LDOBJS_LAST
%.$(EXE_SUFFIX): $(SRC_DIR)$/%.$(LCF_SUFFIX) $(LDOBJS)
	@echo -m2 $(LDFLAGS) $(LIB_DIRS) > $@.txt
	@echo -o ^$@ $(LD_LCF) >> $@.txt 
	@$(foreach i, $(LIBS) $(LDOBJS), echo $i  >>$@.txt & ) 
	$(LD) -@@$@.txt  > $*.map
else
%.$(EXE_SUFFIX): $(SRC_DIR)$/%.$(LCF_SUFFIX) $(LDOBJS)
	@echo -m2 $(LDFLAGS) $(LIB_DIRS) > $@.txt 
	@echo -o ^$@ $(LD_LCF) >> $@.txt  
	@$(foreach i, $(LDOBJS) $(LIBS), echo $i  >>$@.txt & ) 
	$(LD) -@@$@.txt > $*.map
endif
  
else
# Link using a command line.
			                  
ifdef LDOBJS_LAST

ifdef EXE_SUFFIX_INT
%.$(EXE_SUFFIX_INT): $(SRC_DIR)$/%.$(LCF_SUFFIX) $(LDOBJS)
	$(LINK) -o $@ $(LD_LCF) $(LIBS) $(LDOBJS)
else
%.$(EXE_SUFFIX): $(SRC_DIR)$/%.$(LCF_SUFFIX) $(LDOBJS)
	$(LINK) -o $@ $(LD_LCF) $(LIBS) $(LDOBJS)
endif

else

ifdef EXE_SUFFIX_INT
%.$(EXE_SUFFIX_INT): $(SRC_DIR)$/%.$(LCF_SUFFIX) $(LDOBJS)
	$(LINK) -o $@ $(LD_LCF) $(LDOBJS) $(LIBS)
else
%.$(EXE_SUFFIX): $(SRC_DIR)$/%.$(LCF_SUFFIX) $(LDOBJS)
	$(LINK) -o $@ $(LD_LCF) $(LDOBJS) $(LIBS)
endif

endif
endif


ifdef ELF_FROM_EXE_COMMANDS
# %.elf - rule to make elf file from an exe
#
ifdef ELF_FROM_EXE_SUFFIX
%.elf: %.$(ELF_FROM_EXE_SUFFIX)
	$(ELF_FROM_EXE_COMMANDS)
else
%.elf: %.$(EXE_SUFFIX)
	$(ELF_FROM_EXE_COMMANDS)
endif
endif


ifdef MOT_FROM_EXE_COMMANDS
# %.mot - rule to make motorola hex file from exe
#
ifdef MOT_FROM_EXE_SUFFIX
%.mot: %.$(MOT_FROM_EXE_SUFFIX)
	$(MOT_FROM_EXE_COMMANDS)
else
%.mot: %.$(EXE_SUFFIX)
	$(MOT_FROM_EXE_COMMANDS)
endif
else
ifdef MOT_FROM_LCF

# %.mot - rule to make motorola hex file from linking
#

ifdef LD_FROM_FILE
# Link using a text file for the command line options.
ifdef LDOBJS_LAST
%.mot: $(SRC_DIR)$/%.$(LCF_SUFFIX) $(LDOBJS)
	@echo -m2 $(LDFLAGS) $(LIB_DIRS) > $@.txt
	@echo -o ^$@ $(LD_LCF) >> $@.txt 
	@$(foreach i, $(LIBS) $(LDOBJS), echo $i  >>$@.txt & ) 
	$(LD) -@@$@.txt  > $*.map
else
%.mot: $(SRC_DIR)$/%.$(LCF_SUFFIX) $(LDOBJS)
	@echo -m2 $(LDFLAGS) $(LIB_DIRS) > $@.txt
	@echo -o ^$@ $(LD_LCF) >> $@.txt 
	@$(foreach i, $(LDOBJS) $(LIBS), echo $i  >>$@.txt & ) 
	$(LD) -@@$@.txt  > $*.map
endif

else
# Link using a command line.

ifdef LDOBJS_LAST
%.mot: $(SRC_DIR)$/%.$(LCF_SUFFIX) $(LDOBJS)
	$(LINK) -o $@ $(LD_LCF) $(LIBS) $(LDOBJS)
else
%.mot: $(SRC_DIR)$/%.$(LCF_SUFFIX) $(LDOBJS)
	$(LINK) -o $@ $(LD_LCF) $(LDOBJS) $(LIBS)
endif

endif

endif
endif

# %.fls - rule to make motorola hex file from %.opt %.mot
#
%.fls: $(SRC_DIR)$/%.opt %.mot
	$(HCONV) -s -o $^

# help - provide help
#
help:
	@$(ECHO)Targets:$(ECHOEND) 
	@$(ECHO)  all - build app$(ECHOEND) 
	@$(ECHO)  app - build all objects, executables, and flash files$(ECHOEND) 
	@$(ECHO)  $(EXES) - specific executables$(ECHOEND) 
	@$(ECHO)  $(FLSS) - specific flash files$(ECHOEND) 
	@$(ECHO)  $(OBJS) - specific object$(ECHOEND) 
	@$(ECHOEMPTY)

endif


########################################
# building lib or app
########################################
ifdef BUILDING_OBJS


%.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -o $@ $<

%.o: $(SRC_DIR)$/%.cc
	$(COMPILE.cc) -o $@ $<

%.o: $(SRC_DIR)$/%.cpp
	$(COMPILE.cc) -o $@ $<

%.o: $(SRC_DIR)$/%.s
	$(COMPILE.s) -o $@ $<


# rules for platform specific object from
# common source with conditional code
#
%_b5m1i1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DB5M1I1 -o $@ $<

%_a5m1i1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA5M1I1 -o $@ $<

%_a5m2i1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA5M2I1 -o $@ $<
    
%_a4e1v1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA4E1V1 -o $@ $<

%_e2_pi1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DE2_PI1 -o $@ $<

%_a4e2i2.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA4E2I2 -o $@ $<

%_e3_pi1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DE3_PI1 -o $@ $<

%_e4_pi1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DE4_PI1 -o $@ $<

%_e4_pi2.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DE4_PI2 -o $@ $<

%_a4l3i1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA4L3I1 -o $@ $<

%_m1_pi2.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DM1_PI2 -o $@ $<

%_a4n1i1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA4N1I1 -o $@ $<

%_n2_pi1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DN2_PI1 -o $@ $<

%_a4ism1i1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA4ISM1I1 -o $@ $<

%_a4pwc1i1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA4PWC1I1 -o $@ $<

%_a4e1schi1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA4E1SCHI1 -o $@ $<

%_a4m1schi1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA4M1SCHI1 -o $@ $<

%_a4e4i3.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA4E4I3 -o $@ $<

%_a5e1.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA5E1 -o $@ $<

%_a5e2.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA5E2 -o $@ $<

%_a5e4.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA5E4 -o $@ $<

%_a5e4chan.o: $(SRC_DIR)$/%.c
	$(COMPILE.c) -DA5E4CHAN -o $@ $<

endif
