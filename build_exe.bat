@echo off

REM ===== 设置路径 =====
set BUILD_MODE=Release
set PLATFORM=x86
set SLN_PATH=D:\project\Test-jenkins\Test_jenkins\Test_jenkins.sln
set EXE_NAME=Test_jenkins.exe
set BUILD_DIR=D:\project\Test-jenkins\Test_jenkins\Release
set QT_BIN=D:\Qt\5.15.2\msvc2019\bin

REM ===== 编译项目 =====
echo Building...
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
msbuild "%SLN_PATH%" /p:Configuration=%BUILD_MODE%;Platform=%PLATFORM%

REM ===== 使用 windeployqt 拷贝依赖 =====
echo Copying Qt dependencies...
%QT_BIN%\windeployqt.exe "%BUILD_DIR%\%EXE_NAME%"

echo Build and packaging completed.
