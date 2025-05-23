@echo off
echo Running unit tests...
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

set OUTPUT_DIR=Test_jenkins\%BRANCH_NAME%_Release
set BUILD_DIR=%OUTPUT_DIR%

Test_jenkins\test_static_Release\Test_jenkins_test.exe -xml -o %BUILD_DIR%/test_result.xml
IF %ERRORLEVEL% NEQ 0 (
    echo  Unit tests failed.
    pause >nul
    exit /b 1
)
echo  Tests passed.
pause >nul
exit /b 0
