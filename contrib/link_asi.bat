@echo off
rem Check for admin rights
net session >nul 2>&1
if not %errorlevel% == 0 (
	echo This script needs to be run as administrator!
	pause
	exit
)

set pwd=%~dp0

:scriptdir_loop
set /p scriptdir="GTA SA 'scripts' directory path: "
if "%scriptdir%"=="" (
	echo Invalid path!
	goto scriptdir_loop
)

set /p scriptname="Name of the script file (default: gta_reversed): "
if "%scriptname%"=="" set scriptname="gta_reversed"

:scriptconf_loop
set /p scriptconf="Choose configuration to link (debug/release, default: debug): "
if "%scriptconf%"=="" set scriptconf=debug

if not "%scriptconf%"=="debug" if not "%scriptconf%"=="release" (
	echo Invalid configuration! Only 'debug' and 'release' is applicable!c
	goto scriptconf_loop
)

mklink "%scriptdir%\%scriptname%.asi" "%pwd%\..\bin\%scriptconf%\gta_reversed.asi"
mklink "%scriptdir%\%scriptname%.pdb" "%pwd%\..\bin\%scriptconf%\gta_reversed.pdb"

pause