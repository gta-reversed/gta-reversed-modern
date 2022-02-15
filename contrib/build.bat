@echo off
REM cd to the script directory
cd %~dp0\..

REM check for CMake
where cmake>NUL
if %errorlevel% neq 0 (
	echo CMake is required to use this tool. Exiting.
	exit
)

cmake -Bbuild -H. -A Win32
cmake --build build