cls
@echo off
IF EXIST ..\build\.vs rmdir /s /q ..\build\.vs
IF EXIST ..\build\PR_Demo_Workspace rmdir /s /q ..\build\PR_Demo_Workspace
IF EXIST ..\bin\debug rmdir /s /q ..\bin\debug
IF EXIST ..\bin\release rmdir /s /q ..\bin\release
IF EXIST ..\build rmdir /s /q ..\build
IF EXIST ..\bin rmdir /s /q ..\bin

IF EXIST ..\build\EDK_Workspace_vs2017.sln del /F ..\build\EDK_Workspace_vs2017.sln
IF EXIST ..\build\EDK_Workspace_vs2019.sln del /F ..\build\EDK_Workspace_vs2019.sln
