@echo off
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
set EXE_NAME=Test_jenkins.exe
set PROJECT_ROOT=D:\project\Test-jenkins\Test_jenkins
set SLN_PATH=%PROJECT_ROOT%\Test_jenkins.sln
set BUILD_DIR=%PROJECT_ROOT%\%BRANCH_NAME%_Release

REM === 设置 Qt 环境变量 ===
set QTDIR=D:\Qt\5.15.2\msvc2019
set PATH=%QTDIR%\bin;%PATH%

echo  branch: %BRANCH_NAME%
echo  output: %BUILD_DIR%

REM === 构建项目 ===
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
msbuild "%SLN_PATH%" /p:Configuration=%BUILD_MODE%;Platform=%PLATFORM%;QtInstallDir=%QTDIR%

REM === 拷贝 Qt 依赖 ===
%QTDIR%\bin\windeployqt.exe "%BUILD_DIR%\%EXE_NAME%"

echo  "end"。
pause