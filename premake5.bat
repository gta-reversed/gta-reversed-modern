@echo off

rem Generate solution
premake5 vs2019
start "" "%~dp0\Build\gta_reversed.sln"

pause
