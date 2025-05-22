#pragma once

#include "../Model/UserModel.h"
#include "../View/IPasswordLoginView.h"
#include "../View/IVerificationLoginView.h"
#include "../View/IRegisterView.h"

class LoginPresenter {
public:
    LoginPresenter(
        IPasswordLoginView* passwordView, 
        IVerificationLoginView* verificationView,
        IRegisterView* registerView, 
        UserModel* model
    );
    ~LoginPresenter();

private:
    // 视图
    IPasswordLoginView* passwordLoginView;
    IVerificationLoginView* verificationLoginView;
    IRegisterView* registerView;
    
    // 模型
    UserModel* userModel;

    // 处理器方法
    void handlePasswordLogin();
    void handleVerificationLogin();
    void handleRegister();
    
    // 验证方法
    bool validatePasswordLogin();
    bool validateRegistration();
    bool validateVerification();
}; 