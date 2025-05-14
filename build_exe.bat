@echo off

REM ===== ���û���·�� =====
set BUILD_MODE=Release
set PLATFORM=x86
set SLN_PATH=D:\project\Test-jenkins\Test_jenkins\Test_jenkins.sln
set EXE_NAME=Test_jenkins.exe
set QTDIR=D:\Qt\5.15.2\msvc2019
set PATH=%QTDIR%\bin;%PATH%

REM ===== ��ȡ��ǰ Git ��֧�� =====
for /f "delims=" %%i in ('git rev-parse --abbrev-ref HEAD') do set BRANCH_NAME=%%i

REM ===== �������Ŀ¼���� main_Release��test_Release =====
set OUTPUT_DIR=D:\project\Test-jenkins\Test_jenkins\%BRANCH_NAME%_Release
set BUILD_DIR=%OUTPUT_DIR%

REM ===== Qt ��װ·�� =====
set QT_BIN=%QTDIR%\bin

REM ===== ������Ŀ =====
echo Building [%BRANCH_NAME%]...
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
msbuild "%SLN_PATH%" /p:Configuration=%BUILD_MODE%;Platform=%PLATFORM% /p:OutDir=%OUTPUT_DIR%\ /p:QtInstallDir=%QTDIR%

IF %ERRORLEVEL% NEQ 0 (
    echo Build failed, exiting...
    pause
    exit /b %ERRORLEVEL%
)

REM ===== �������Ŀ¼�����û�У�=====
if not exist "%OUTPUT_DIR%" (
    mkdir "%OUTPUT_DIR%"
)

REM ===== ʹ�� windeployqt �������� =====
echo Deploying Qt dependencies to %OUTPUT_DIR%...
"%QT_BIN%\windeployqt.exe" "%BUILD_DIR%\%EXE_NAME%"

echo Build and deploy completed: %BUILD_DIR%
pause
