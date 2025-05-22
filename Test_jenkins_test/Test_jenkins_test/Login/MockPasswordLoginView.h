#pragma once

#include "Login/View/IPasswordLoginView.h"
#include <QStringList>

class MockPasswordLoginView : public IPasswordLoginView {
public:
    MockPasswordLoginView();
    ~MockPasswordLoginView() override;
    
    // 设置模拟数据
    void setMockUsername(const QString& username);
    void setMockPassword(const QString& password);
    
    // 获取消息历史
    QStringList getMessageHistory() const;
    
    // 触发事件
    void triggerLoginClicked();
    void triggerSwitchToVerificationClicked();
    void triggerRegisterClicked();
    
    // ILoginView接口实现
    void show() override;
    void hide() override;
    void showMessage(const QString& message) override;
    void clearInputs() override;
    
    // IPasswordLoginView接口实现
    QString getUsername() const override;
    QString getPassword() const override;
    void attachOnLoginClicked(std::function<void()> callback) override;
    void attachOnSwitchToVerificationClicked(std::function<void()> callback) override;
    void attachOnRegisterClicked(std::function<void()> callback) override;

private:
    QString m_username;
    QString m_password;
    QStringList m_messageHistory;
    bool m_isShown;
    
    std::function<void()> m_loginCallback;
    std::function<void()> m_switchToVerificationCallback;
    std::function<void()> m_registerCallback;
}; 