#pragma once

#include "../../Modules/Login/View/IVerificationLoginView.h"
#include <QStringList>

class MockVerificationLoginView : public IVerificationLoginView {
public:
    MockVerificationLoginView();
    ~MockVerificationLoginView() override;
    
    // 设置模拟数据
    void setMockVerificationValue(int value);
    
    // 获取消息历史
    QStringList getMessageHistory() const;
    
    // 触发事件
    void triggerVerifyClicked();
    void triggerSwitchToPasswordLoginClicked();
    
    // ILoginView接口实现
    void show() override;
    void hide() override;
    void showMessage(const QString& message) override;
    void clearInputs() override;
    
    // IVerificationLoginView接口实现
    int getVerificationValue() const override;
    void attachOnVerifyClicked(std::function<void()> callback) override;
    void attachOnSwitchToPasswordLoginClicked(std::function<void()> callback) override;

private:
    int m_verificationValue;
    QStringList m_messageHistory;
    bool m_isShown;
    
    std::function<void()> m_verifyCallback;
    std::function<void()> m_switchToPasswordLoginCallback;
}; 