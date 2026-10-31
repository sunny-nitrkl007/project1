@echo off

rem Set path to MATLAB
set PATH=C:\MATLAB_R2007b\bin;%PATH%

rem Set path to CATutils
set CATUTILS_MATLAB=M:\kagyra_050518\lib_autocode\CATutils_MatLab

rem Copy model
copy ..\mdlR13\mdlFloat.mdl .\mdlFloat.mdl

rem GO!
matlab /wait -r convert_and_build_mdlFloat