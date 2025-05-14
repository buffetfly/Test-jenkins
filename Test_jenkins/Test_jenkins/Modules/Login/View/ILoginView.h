#pragma once

#include <QString>
#include <functional>

// 抽象登录视图接口
class ILoginView {
public:
    virtual ~ILoginView() = default;

    // 用于显示和隐藏视图
    virtual void show() = 0;
    virtual void hide() = 0;
    
    // 消息显示
    virtual void showMessage(const QString& message) = 0;
    
    // 清除输入
    virtual void clearInputs() = 0;
}; 