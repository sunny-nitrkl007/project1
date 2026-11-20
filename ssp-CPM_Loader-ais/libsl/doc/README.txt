lib_autocode\lib_simulink\doc\README.txt

This file documents the purpose & use of lib_autocode\lib_simulink.

lib_simulink is meant to be a repository of static functions used with
code generated from Simulink.  Some of the functions are copied from the
MathWorks distribution.  Some of the functions were written here at Caterpillar
and referenced by generated code.

This is NOT meant to be the repository of any static functions that are used by
S-Functions in simulation or on the xPC.  At this time it would be difficult to
build those functions here and then link them in appropriately.  Perhaps this
can be done at a future date.  For the moment this seems ambitious enough.

Building everything
1. Open a Windows command prompt
2. Change directory to lib_simulink\src\makefiles
3. Run the command:
   build_all.cmd

Building the directory tree:
1. Open a command prompt (any)
2. Change directory to lib_simulink\src\makefiles
3. Run the command:
   emake --win32 tree all

Building the diab 4.2b target:
1. Open the command prompt (any)
2. Change to target directory (lib_simulink\tgt_diag_4.2b_PPC555EH)
3. Run the command:
   emake --win32 all

Building the arm target:
  No need to install the compiler, just make sure lib_oel is mounted and ARMLMD_LICENSE_FILE is set
1. Open the command prompt (any)
2. Change to target directory (lib_simulink\tgt_rvct_2.1_ARM7TDMI)
3. Run the command:
   emake --win32 all

Building the cc32r 4.30 target:

NOTE - Cat Electronics only bought one license, and so you can't just do what follows.
NOTE - The CATutils team has purchased one node locked license, so this must be run
       from the PC on which this license is installed.
1. Open the command prompt (any)
2. Run the BATCH file to setup the environment.
3. Run the command:
   emake --win32 all


Building the diab 5.8 target:
  No need to install the compiler, just makes sure the cots_afsw VOB is mounted and the WRSD_LICENSE_FILE environmental variable is set
1. Open the command prompt (any)
2. Change to target directory (lib_simulink\tgt_diab_5.8.0.0_PPCVLEEF)
3. Run the command:
   clearmake all


Because this has gotten long & complicated, and because diab 4.2b now runs from
  a normal Windows command shell, attempted to create a DOS BATCH file to run
  the necessary commands:
  \lib_simulink\src\makefiles\build_all.cmd


Adding a new component:
1. Place public headers in lib_simulink\include
     Public headers are what someone needs to link in the library
		 The public headers should only include headers in public include
		 directories.
2. Create a new directory in lib_simulink\src\lib for the source files
3. If you need any component specific control, edit the defs.mk.  If you don't
   do anything, the options specified in makefiles\defs.mk will be used and all
	 of the .c files found will be compiled and placed in a library.
4. Update \lib_simulink\src\makefiles\Makefile_all.mk


Adding a new target:
Edit the file lib_simulink\src\makefiles\Makefile and add to the TGT_ARCHS list
 - The available targets are in lib_oel\environment\makefiles\tgt_*
 - According to Steve Bray, there is no need to compile once with no floating
   point support, and then again with hardware floating support.  It is only
   important to distinguish software floating point from hardware floating
	 point.


Notes:
 - Don't check in the derived makefiles or object files.  Only need to add the
   tgt directories and any libraries to source control.
 - The directory tree under lib_simulink was originally copied from
   lib_oel\development_template.  AFSW_2007_Q2_PROD appears to be the latest
	 PROD label of the version used.  This is no longer maintained / exists.
 - See some of the HAL components for examples on how to conditionally compile
   for different targets.  One example is lib_a4\hal\src\lib\hal_edma\defs.mk
