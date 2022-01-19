@echo off
set pwd=%~dp0
set scriptdir=%1
set scriptname=%2

if "%scriptdir%"=="" goto :eof
if "%scriptname%"=="" set scriptname="gta_reversed"

mklink %scriptdir%\%scriptname%.asi "%pwd%\..\bin\debug\gta_reversed.asi"
mklink %scriptdir%\%scriptname%.pdb "%pwd%\..\bin\debug\gta_reversed.pdb"

eof: