@echo off

rem Set path to MATLAB
set PATH=C:\MATLAB_R2007b\bin;%PATH%

rem Set path to CATutils
set CATUTILS_MATLAB=M:\kagyra_050518\lib_autocode\CATutils_MatLab

rem GO!
matlab /wait -r build_mdlApp