#include "MockPasswordLoginView.h"

MockPasswordLoginView::MockPasswordLoginView()
    : m_username("test_user"),
      m_password("test_password"),
      m_isShown(false) {
}

MockPasswordLoginView::~MockPasswordLoginView() {
}

void MockPasswordLoginView::setMockUsername(const QString& username) {
    m_username = username;
}

void MockPasswordLoginView::setMockPassword(const QString& password) {
    m_password = password;
}

QStringList MockPasswordLoginView::getMessageHistory() const {
    return m_messageHistory;
}

void MockPasswordLoginView::triggerLoginClicked() {
    if (m_loginCallback) {
        m_loginCallback();
    }
}

void MockPasswordLoginView::triggerSwitchToVerificationClicked() {
    if (m_switchToVerificationCallback) {
        m_switchToVerificationCallback();
    }
}

void MockPasswordLoginView::triggerRegisterClicked() {
    if (m_registerCallback) {
        m_registerCallback();
    }
}

void MockPasswordLoginView::show() {
    m_isShown = true;
}

void MockPasswordLoginView::hide() {
    m_isShown = false;
}

void MockPasswordLoginView::showMessage(const QString& message) {
    m_messageHistory.append(message);
}

void MockPasswordLoginView::clearInputs() {
    // 在测试中不实际清除输入
}

QString MockPasswordLoginView::getUsername() const {
    return m_username;
}

QString MockPasswordLoginView::getPassword() const {
    return m_password;
}

void MockPasswordLoginView::attachOnLoginClicked(std::function<void()> callback) {
    m_loginCallback = callback;
}

void MockPasswordLoginView::attachOnSwitchToVerificationClicked(std::function<void()> callback) {
    m_switchToVerificationCallback = callback;
}

void MockPasswordLoginView::attachOnRegisterClicked(std::function<void()> callback) {
    m_registerCallback = callback;
} 