#pragma once

#include "../Presenter/LoginPresenter.h"
#include "../View/IPasswordLoginView.h"
#include "../View/IVerificationLoginView.h"
#include "../View/IRegisterView.h"
#include "../Model/UserModel.h"

class LoginCoordinator {
public:
    LoginCoordinator(IPasswordLoginView*, IVerificationLoginView*, IRegisterView*);
    ~LoginCoordinator();

    void start();

private:
    // 视图
    IPasswordLoginView* passwordLoginView;
    IVerificationLoginView* verificationLoginView;
    IRegisterView* registerView;
    
    // 模型
    UserModel* userModel;
    
    // 当前活跃的视图
    ILoginView* activeView;
    
    // Presenter
    LoginPresenter* loginPresenter;
    
    // 导航回调
    void navigateToPasswordLogin();
    void navigateToVerificationLogin();
    void navigateToRegister();
}; 