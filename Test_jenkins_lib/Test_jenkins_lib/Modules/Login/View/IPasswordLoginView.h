#pragma once

#include "ILoginView.h"

// 用户名密码登录视图接口
class IPasswordLoginView : public ILoginView {
public:
    // 获取用户名和密码
    virtual QString getUsername() const = 0;
    virtual QString getPassword() const = 0;
    
    // 事件回调
    virtual void attachOnLoginClicked(std::function<void()> callback) = 0;
    virtual void attachOnSwitchToVerificationClicked(std::function<void()> callback) = 0;
    virtual void attachOnRegisterClicked(std::function<void()> callback) = 0;
}; 