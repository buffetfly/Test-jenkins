#include <QApplication>
#include <QTextCodec>
#include "Login/Coordinator/LoginCoordinator.h"
#include "Modules/Login/View/QtPasswordLoginView.h"
#include "Modules/Login/View/QtRegisterView.h"
#include "Modules/Login/View/QtVerificationLoginView.h"

// 自动运行所有测试类的宏
int main(int argc, char* argv[])
{
    // 设置Qt应用程序
    QApplication app(argc, argv);

    QTextCodec* codec = QTextCodec::codecForName("GBK");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);

     LoginCoordinator coordinator(new QtPasswordLoginView(), new QtVerificationLoginView(), new QtRegisterView());
     coordinator.start();
     return app.exec();
}
