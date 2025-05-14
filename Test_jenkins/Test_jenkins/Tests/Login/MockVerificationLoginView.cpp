#include "MockVerificationLoginView.h"

MockVerificationLoginView::MockVerificationLoginView()
    : m_verificationValue(75),
      m_isShown(false) {
}

MockVerificationLoginView::~MockVerificationLoginView() {
}

void MockVerificationLoginView::setMockVerificationValue(int value) {
    m_verificationValue = value;
}

QStringList MockVerificationLoginView::getMessageHistory() const {
    return m_messageHistory;
}

void MockVerificationLoginView::triggerVerifyClicked() {
    if (m_verifyCallback) {
        m_verifyCallback();
    }
}

void MockVerificationLoginView::triggerSwitchToPasswordLoginClicked() {
    if (m_switchToPasswordLoginCallback) {
        m_switchToPasswordLoginCallback();
    }
}

void MockVerificationLoginView::show() {
    m_isShown = true;
}

void MockVerificationLoginView::hide() {
    m_isShown = false;
}

void MockVerificationLoginView::showMessage(const QString& message) {
    m_messageHistory.append(message);
}

void MockVerificationLoginView::clearInputs() {
    // 在测试中不实际清除输入
}

int MockVerificationLoginView::getVerificationValue() const {
    return m_verificationValue;
}

void MockVerificationLoginView::attachOnVerifyClicked(std::function<void()> callback) {
    m_verifyCallback = callback;
}

void MockVerificationLoginView::attachOnSwitchToPasswordLoginClicked(std::function<void()> callback) {
    m_switchToPasswordLoginCallback = callback;
} 