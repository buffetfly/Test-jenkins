@echo off
echo Running unit tests...
setlocal enabledelayedexpansion
REM === ������������ Jenkins ���� GIT_BRANCH������ origin/test�� ===
set FULL_BRANCH=%1
for /f "tokens=2 delims=/" %%i in ("%FULL_BRANCH%") do (
    set BRANCH_NAME=%%i
)

REM ���δ��������������� git ��ȡ�������ֶ�����ʱ�ã�
if not defined BRANCH_NAME (
    for /f %%i in ('git rev-parse --abbrev-ref HEAD') do (
        set BRANCH_NAME=%%i
    )
)

set OUTPUT_DIR=D:\project\Test-jenkins\Test_jenkins\%BRANCH_NAME%_Release
set BUILD_DIR=%OUTPUT_DIR%

D:\project\Test-jenkins\Test_jenkins\test_static_Release\Test_jenkins_test.exe -xml -o %BUILD_DIR%/test_result.xml
IF %ERRORLEVEL% NEQ 0 (
    echo  Unit tests failed.
    pause >nul
    exit /b 1
)
echo  Tests passed.
pause >nul
exit /b 0