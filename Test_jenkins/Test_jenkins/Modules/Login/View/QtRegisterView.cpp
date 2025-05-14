#include "QtRegisterView.h"
#include "ui_QtRegisterView.h"
#include <QMessageBox>

QtRegisterView::QtRegisterView(QWidget* parent)
    : QWidget(parent), ui(new Ui::QtRegisterView) {
    ui->setupUi(this);

    // 连接信号和槽
    connect(ui->registerSubmitButton, &QPushButton::clicked, this, &QtRegisterView::onRegisterSubmitClicked);
    connect(ui->backToLoginButton, &QPushButton::clicked, this, &QtRegisterView::onBackToLoginClicked);
}

QtRegisterView::~QtRegisterView() {
    delete ui;
}

QString QtRegisterView::getUsername() const {
    return ui->newUsernameEdit->text();
}

QString QtRegisterView::getPassword() const {
    return ui->newPasswordEdit->text();
}

QString QtRegisterView::getConfirmPassword() const {
    return ui->confirmPasswordEdit->text();
}

void QtRegisterView::showMessage(const QString& message) {
    QMessageBox::information(this, "提示", message);
}

void QtRegisterView::clearInputs() {
    ui->newUsernameEdit->clear();
    ui->newPasswordEdit->clear();
    ui->confirmPasswordEdit->clear();
}

void QtRegisterView::show() {
    QWidget::show();
}

void QtRegisterView::hide() {
    QWidget::hide();
}

void QtRegisterView::attachOnRegisterSubmitClicked(std::function<void()> callback) {
    registerSubmitCallback = callback;
}

void QtRegisterView::attachOnBackToLoginClicked(std::function<void()> callback) {
    backToLoginCallback = callback;
}

void QtRegisterView::onRegisterSubmitClicked() {
    if (registerSubmitCallback) {
        registerSubmitCallback();
    }
}

void QtRegisterView::onBackToLoginClicked() {
    if (backToLoginCallback) {
        backToLoginCallback();
    }
}