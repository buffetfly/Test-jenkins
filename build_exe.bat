@echo off
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

REM === �������� ===
set BUILD_MODE=Release
set PLATFORM=x86
set EXE_NAME=Test_jenkins.exe
set PROJECT_ROOT=D:\project\Test-jenkins\Test_jenkins
set SLN_PATH=%PROJECT_ROOT%\Test_jenkins.sln
set BUILD_DIR=%PROJECT_ROOT%\%BRANCH_NAME%_Release

REM === ���� Qt �������� ===
set QTDIR=D:\Qt\5.15.2\msvc2019
set PATH=%QTDIR%\bin;%PATH%

echo  branch: %BRANCH_NAME%
echo  output: %BUILD_DIR%

REM === ������Ŀ ===
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
msbuild "%SLN_PATH%" /p:Configuration=%BUILD_MODE%;Platform=%PLATFORM%;QtInstallDir=%QTDIR%

REM === ���� Qt ���� ===
%QTDIR%\bin\windeployqt.exe "%BUILD_DIR%\%EXE_NAME%"

echo  "end"��
pause