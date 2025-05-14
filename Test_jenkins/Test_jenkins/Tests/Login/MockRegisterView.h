#pragma once

#include "../../Modules/Login/View/IRegisterView.h"
#include <QStringList>

class MockRegisterView : public IRegisterView {
public:
    MockRegisterView();
    ~MockRegisterView() override;
    
    // 设置模拟数据
    void setMockUsername(const QString& username);
    void setMockPassword(const QString& password);
    void setMockConfirmPassword(const QString& confirmPassword);
    
    // 获取消息历史
    QStringList getMessageHistory() const;
    
    // 触发事件
    void triggerRegisterSubmitClicked();
    void triggerBackToLoginClicked();
    
    // ILoginView接口实现
    void show() override;
    void hide() override;
    void showMessage(const QString& message) override;
    void clearInputs() override;
    
    // IRegisterView接口实现
    QString getUsername() const override;
    QString getPassword() const override;
    QString getConfirmPassword() const override;
    void attachOnRegisterSubmitClicked(std::function<void()> callback) override;
    void attachOnBackToLoginClicked(std::function<void()> callback) override;

private:
    QString m_username;
    QString m_password;
    QString m_confirmPassword;
    QStringList m_messageHistory;
    bool m_isShown;
    
    std::function<void()> m_registerSubmitCallback;
    std::function<void()> m_backToLoginCallback;
}; 