#pragma once

#include "ILoginView.h"

// 人机验证登录视图接口
class IVerificationLoginView : public ILoginView {
public:
    // 获取验证值
    virtual int getVerificationValue() const = 0;
    
    // 事件回调
    virtual void attachOnVerifyClicked(std::function<void()> callback) = 0;
    virtual void attachOnSwitchToPasswordLoginClicked(std::function<void()> callback) = 0;
}; 
