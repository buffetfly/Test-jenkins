#include "Test_jenkins.h"

Test_jenkins::Test_jenkins(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Test_jenkinsClass())
{
    ui->setupUi(this);
}

Test_jenkins::~Test_jenkins()
{
    delete ui;
}
