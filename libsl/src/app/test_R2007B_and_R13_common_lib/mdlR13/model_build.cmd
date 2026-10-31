@echo off
rem Build model
rem   Couldn't figure out how to adjust environment from Windows

rem Get working version of PERL
set PATH=C:\MATLAB_R2007b\sys\perl\win32\bin;%PATH%
rem Generate code
echo PATH=%PATH%
echo about to call model_build.bat
call M:\kagyra_080214_R13_Development\lib_autocode\CATutils_MatLab\toolbox\makefile_build\model_build.bat %1