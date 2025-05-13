#pragma once

#include <QtWidgets/QWidget>
#include "ui_Test_jenkins.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Test_jenkinsClass; };
QT_END_NAMESPACE

class Test_jenkins : public QWidget
{
    Q_OBJECT

public:
    Test_jenkins(QWidget *parent = nullptr);
    ~Test_jenkins();

private:
    Ui::Test_jenkinsClass *ui;
};
