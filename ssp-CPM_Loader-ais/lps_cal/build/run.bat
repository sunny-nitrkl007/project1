ECHO ON

CLS
cd /
cd C:\Users\gundas1\ivy\lps_cal\lib\lib_machine_productivity\lps\cal\lps_cal\build

emake --win32 -f makefile_diab_5_8 clean
emake --win32 -f makefile_diab_5_8

PAUSE
