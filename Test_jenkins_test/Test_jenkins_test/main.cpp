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

// �Զ��������в�����ĺ�

int main(int argc, char* argv[])
{
    // ����QtӦ�ó���
    QCoreApplication app(argc, argv);


    QTextCodec* codec = QTextCodec::codecForName("GBK");//����"GBK",���ִ�Сд
    QTextCodec::setCodecForLocale(codec);

    // �������в�����
    QTEST_RUN_TEST(LoginPresenterTest)
        // δ��������Ӹ��������
// QTEST_RUN_TEST(AnotherTest)
return 0;
}
