#include <QApplication>
#include <QTest>
#include <QTextCodec>
#include "Login/Coordinator/LoginCoordinator.h"
#include "Login/LoginPresenterTest.h"

#define RUN_TESTS
#define QTEST_RUN_TEST(TestClass) { \
    TestClass tc; \
    QTest::qExec(&tc); \
}

// 自动运行所有测试类的宏

int main(int argc, char* argv[])
{
    // 设置Qt应用程序
    QCoreApplication app(argc, argv);


    QTextCodec* codec = QTextCodec::codecForName("GBK");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);

    // 运行所有测试类
    QTEST_RUN_TEST(LoginPresenterTest)
        // 未来可以添加更多测试类
// QTEST_RUN_TEST(AnotherTest)
return 0;
}
