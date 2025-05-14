#include <QApplication>
#include <QTest>
#include "Modules/Login/Coordinator/LoginCoordinator.h"
#include "Tests/Login/LoginPresenterTest.h"

// 定义宏控制模式
// 如果定义了USE_UI，则启用UI界面
// 如果定义了RUN_TESTS，则运行单元测试
#define USE_UI 1
//#define RUN_TESTS 1

#ifdef RUN_TESTS
#define QTEST_RUN_TEST(TestClass) { \
    TestClass tc; \
    QTest::qExec(&tc); \
}
#endif


// 自动运行所有测试类的宏


int main(int argc, char* argv[])
{
    // 设置Qt应用程序
#ifdef RUN_TESTS
    QCoreApplication app(argc, argv);
#else
    QApplication app(argc, argv);
#endif

    QTextCodec* codec = QTextCodec::codecForName("GBK");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);

#ifdef RUN_TESTS
    // 运行所有测试类
    QTEST_RUN_TEST(LoginPresenterTest)
        // 未来可以添加更多测试类
// QTEST_RUN_TEST(AnotherTest)
    return 0;
#else
     LoginCoordinator coordinator;
     coordinator.start();
     return app.exec();
#endif

}
