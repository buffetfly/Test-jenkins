﻿@echo off
setlocal enabledelayedexpansion

REM === 参数解析（从 Jenkins 传入 GIT_BRANCH，例如 origin/test） ===
set FULL_BRANCH=%1
for /f "tokens=2 delims=/" %%i in ("%FULL_BRANCH%") do (
    set BRANCH_NAME=%%i
)

REM 如果未传入参数，则尝试用 git 获取（本地手动运行时用）
if not defined BRANCH_NAME (
    for /f %%i in ('git rev-parse --abbrev-ref HEAD') do (
        set BRANCH_NAME=%%i
    )
)

REM === 编译配置 ===
set BUILD_MODE=Release
set PLATFORM=x86
set SLN_PATH=D:\project\Test-jenkins\Test_jenkins\Test_jenkins.sln
set EXE_NAME=Test_jenkins.exe
set QTDIR=D:\Qt\5.15.2\msvc2019
set PATH=%QTDIR%\bin;%PATH%
set QT_BIN=%QTDIR%\bin
echo  branch: %BRANCH_NAME%

REM ===== 设置输出目录：如 main_Release、test_Release =====
set OUTPUT_DIR=D:\project\Test-jenkins\Test_jenkins\%BRANCH_NAME%_Release
set BUILD_DIR=%OUTPUT_DIR%

REM ===== 编译项目 =====
echo Building [%BRANCH_NAME%]...
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
msbuild "%SLN_PATH%" /p:Configuration=%BUILD_MODE%;Platform=%PLATFORM% /p:OutDir=%OUTPUT_DIR%\ /p:QtInstallDir=%QTDIR%

IF %ERRORLEVEL% NEQ 0 (
    echo Build failed, exiting...
    pause
    exit /b %ERRORLEVEL%
)

REM ===== 创建输出目录（如果没有）=====
if not exist "%OUTPUT_DIR%" (
    mkdir "%OUTPUT_DIR%"
)

REM ===== 使用 windeployqt 拷贝依赖 =====
echo Deploying Qt dependencies to %OUTPUT_DIR%...
"%QT_BIN%\windeployqt.exe" "%BUILD_DIR%\%EXE_NAME%"

echo Build and deploy completed: %BUILD_DIR%
pause