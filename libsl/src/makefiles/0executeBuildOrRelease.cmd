@ECHO OFF
REM 0executeBuildOrRelease.cmd
REM   Launcher for Python script to execute build or release process

REM -------------------------------------------------------------------------
REM This script depends on the Command Extensions introduced in Win2000 being
REM enabled.  See help setlocal for the following code snippet
REM -------------------------------------------------------------------------
VERIFY other 2>NUL
SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
IF ERRORLEVEL 1 (
	ECHO Old version of cmd.exe without Command Extensions!
	EXIT
)
IF NOT CMDEXTVERSION 1 (
	ECHO Command Extensions disabled, Batch file will not run
	EXIT 99
)

REM -------------------------------------------------------------------------
REM Launch Python
REM -------------------------------------------------------------------------

REM Ensure we're in makefiles directory
SET "MYPATH=%~dp0"
CD /D "%MYPATH%"

REM Relative to view root, we're at:
REM   \lib_autocode_release\lib_simulink\src\makefiles
REM Launch Python at:
REM   \com.portablepython\oss\portable_python\2.7.6.1\python.exe
"..\..\..\..\com.portablepython\oss\portable_python\2.7.6.1\python.exe" -tt 0executeBuildOrRelease.py

REM -------------------------------------------------------------------------
REM Wait for exit
REM -------------------------------------------------------------------------
IF ERRORLEVEL 1 (
    ECHO Build process appears to have had errors
) ELSE (
	ECHO Build process appears to have completed successfully.
)
PAUSE
