echo Running unit tests...
D:\project\Test-jenkins\Test_jenkins\test_static_Release\Test_jenkins_test.exe -xml -o D:/project/Test-jenkins/test_result.xml
IF %ERRORLEVEL% NEQ 0 (
    echo  Unit tests failed.
    pause >nul
    exit /b 1
)
echo  Tests passed.
pause >nul