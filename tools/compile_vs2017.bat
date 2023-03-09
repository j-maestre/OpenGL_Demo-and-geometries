@ECHO off
cls
.\GENie\genie.exe vs2017

xcopy /s /d /Y .\..\assets .\..\bin\debug\x32
xcopy /s /d /Y .\..\assets .\..\bin\release\x32

xcopy /s /d /Y .\..\assets .\..\build\PR_Demo_Workspace\vs2017

pause
