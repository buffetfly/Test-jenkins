#include "MockRegisterView.h"

MockRegisterView::MockRegisterView()
    : m_username("new_user"),
      m_password("new_password"),
      m_confirmPassword("new_password"),
      m_isShown(false) {
}

MockRegisterView::~MockRegisterView() {
}

void MockRegisterView::setMockUsername(const QString& username) {
    m_username = username;
}

void MockRegisterView::setMockPassword(const QString& password) {
    m_password = password;
}

void MockRegisterView::setMockConfirmPassword(const QString& confirmPassword) {
    m_confirmPassword = confirmPassword;
}

QStringList MockRegisterView::getMessageHistory() const {
    return m_messageHistory;
}

void MockRegisterView::triggerRegisterSubmitClicked() {
    if (m_registerSubmitCallback) {
        m_registerSubmitCallback();
    }
}

void MockRegisterView::triggerBackToLoginClicked() {
    if (m_backToLoginCallback) {
        m_backToLoginCallback();
    }
}

void MockRegisterView::show() {
    m_isShown = true;
}

void MockRegisterView::hide() {
    m_isShown = false;
}

void MockRegisterView::showMessage(const QString& message) {
    m_messageHistory.append(message);
}

void MockRegisterView::clearInputs() {
    // 在测试中不实际清除输入
}

QString MockRegisterView::getUsername() const {
    return m_username;
}

QString MockRegisterView::getPassword() const {
    return m_password;
}

QString MockRegisterView::getConfirmPassword() const {
    return m_confirmPassword;
}

void MockRegisterView::attachOnRegisterSubmitClicked(std::function<void()> callback) {
    m_registerSubmitCallback = callback;
}

void MockRegisterView::attachOnBackToLoginClicked(std::function<void()> callback) {
    m_backToLoginCallback = callback;
} 