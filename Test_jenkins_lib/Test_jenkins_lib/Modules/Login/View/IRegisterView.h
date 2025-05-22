#pragma once

#include "ILoginView.h"

// 用户注册视图接口
class IRegisterView : public ILoginView {
public:
    // 获取注册信息
    virtual QString getUsername() const = 0;
    virtual QString getPassword() const = 0;
    virtual QString getConfirmPassword() const = 0;
    
    // 事件回调
    virtual void attachOnRegisterSubmitClicked(std::function<void()> callback) = 0;
    virtual void attachOnBackToLoginClicked(std::function<void()> callback) = 0;
}; 