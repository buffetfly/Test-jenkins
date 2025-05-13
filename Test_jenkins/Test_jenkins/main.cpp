#include "Test_jenkins.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Test_jenkins w;
    w.show();
    return a.exec();
}
