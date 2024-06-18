@echo off

rem Check first arg for VS version, use vs2022 if empty
set VSVER=%1
if "%VSVER%"=="" set VSVER=vs2022
rem Generate solution
premake5 %VSVER%
rem Create a shortcut to the solution - http://superuser.com/questions/392061/how-to-make-a-shortcut-from-cmd
set SCRIPTFILE="%TEMP%\CreateMyShortcut.vbs"
(
  echo Set oWS = WScript.CreateObject^("WScript.Shell"^) 
  echo sLinkFile = oWS.ExpandEnvironmentStrings^("gta_sa_modern.sln - Shortcut.lnk"^)
  echo Set oLink = oWS.CreateShortcut^(sLinkFile^) 
  echo oLink.TargetPath = oWS.ExpandEnvironmentStrings^("%~dp0\build\gta_sa_modern.sln"^)
  echo oLink.Save
) 1>%SCRIPTFILE%
cscript //nologo %SCRIPTFILE%
del /f /q %SCRIPTFILE%

pause
