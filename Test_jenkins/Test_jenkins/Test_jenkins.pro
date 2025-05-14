TEMPLATE = app
QT += core gui testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# 项目输出目录
DESTDIR = $$PWD/bin

# 定义测试模式宏
CONFIG(test) {
    TARGET = Test_jenkins_test
    DEFINES += RUN_TESTS
} else {
    TARGET = Test_jenkins
}

# 头文件
HEADERS += \
    GlobalEncoding.h \
    Modules/Login/View/ILoginView.h \
    Modules/Login/View/IPasswordLoginView.h \
    Modules/Login/View/IVerificationLoginView.h \
    Modules/Login/View/IRegisterView.h \
    Modules/Login/Model/UserModel.h \
    Modules/Login/Presenter/LoginPresenter.h \
    Modules/Login/Coordinator/LoginCoordinator.h

# 源文件
SOURCES += \
    Modules/Login/Model/UserModel.cpp \
    Modules/Login/Presenter/LoginPresenter.cpp \
    Modules/Login/Coordinator/LoginCoordinator.cpp

# UI模式特有的文件
!CONFIG(test) {
    HEADERS += \
        Modules/Login/View/QtPasswordLoginView.h \
        Modules/Login/View/QtVerificationLoginView.h \
        Modules/Login/View/QtRegisterView.h
    
    SOURCES += \
        main.cpp \
        Modules/Login/View/QtPasswordLoginView.cpp \
        Modules/Login/View/QtVerificationLoginView.cpp \
        Modules/Login/View/QtRegisterView.cpp
    
    FORMS += \
        Modules/Login/View/QtPasswordLoginView.ui \
        Modules/Login/View/QtVerificationLoginView.ui \
        Modules/Login/View/QtRegisterView.ui
}

# 测试模式特有的文件
CONFIG(test) {
    HEADERS += \
        Tests/Login/MockPasswordLoginView.h \
        Tests/Login/MockVerificationLoginView.h \
        Tests/Login/MockRegisterView.h \
        Tests/Login/LoginPresenterTest.h
    
    SOURCES += \
        Tests/main_test.cpp \
        Tests/Login/MockPasswordLoginView.cpp \
        Tests/Login/MockVerificationLoginView.cpp \
        Tests/Login/MockRegisterView.cpp \
        Tests/Login/LoginPresenterTest.cpp
}

# 资源文件
RESOURCES += \
    Test_jenkins.qrc

# 编译选项
QMAKE_CXXFLAGS_WARN_ON += -Wall -Wextra
win32:QMAKE_CXXFLAGS += -execution-charset:utf-8
macx:QMAKE_CXXFLAGS += -fconstant-cfstrings

# 默认规则，用于生成目标
target.path = /bin
!isEmpty(target.path): INSTALLS += target 