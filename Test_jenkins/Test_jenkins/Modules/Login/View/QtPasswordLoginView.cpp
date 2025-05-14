#include "QtPasswordLoginView.h"
#include "ui_QtPasswordLoginView.h"
#include <QMessageBox>

QtPasswordLoginView::QtPasswordLoginView(QWidget* parent)
    : QWidget(parent), ui(new Ui::QtPasswordLoginView) {
    ui->setupUi(this);

    // 连接信号和槽
    connect(ui->loginButton, &QPushButton::clicked, this, &QtPasswordLoginView::onLoginClicked);
    connect(ui->switchToVerifyButton, &QPushButton::clicked, this, &QtPasswordLoginView::onSwitchToVerificationClicked);
    connect(ui->switchToRegisterButton, &QPushButton::clicked, this, &QtPasswordLoginView::onRegisterClicked);
}

QtPasswordLoginView::~QtPasswordLoginView() {
    delete ui;
}

QString QtPasswordLoginView::getUsername() const {
    return ui->usernameEdit->text();
}

QString QtPasswordLoginView::getPassword() const {
    return ui->passwordEdit->text();
}

void QtPasswordLoginView::showMessage(const QString& message) {
    QMessageBox::information(this, u8"提示", message);
}

void QtPasswordLoginView::clearInputs() {
    ui->usernameEdit->clear();
    ui->passwordEdit->clear();
}

void QtPasswordLoginView::show() {
    QWidget::show();
}

void QtPasswordLoginView::hide() {
    QWidget::hide();
}

void QtPasswordLoginView::attachOnLoginClicked(std::function<void()> callback) {
    loginCallback = callback;
}

void QtPasswordLoginView::attachOnSwitchToVerificationClicked(std::function<void()> callback) {
    switchToVerificationCallback = callback;
}

void QtPasswordLoginView::attachOnRegisterClicked(std::function<void()> callback) {
    registerCallback = callback;
}

void QtPasswordLoginView::onLoginClicked() {
    if (loginCallback) {
        loginCallback();
    }
}

void QtPasswordLoginView::onSwitchToVerificationClicked() {
    if (switchToVerificationCallback) {
        switchToVerificationCallback();
    }
}

void QtPasswordLoginView::onRegisterClicked() {
    if (registerCallback) {
        registerCallback();
    }
}