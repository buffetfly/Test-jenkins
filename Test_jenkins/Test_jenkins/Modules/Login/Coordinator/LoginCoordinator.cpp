#include "LoginCoordinator.h"

LoginCoordinator::LoginCoordinator() {
    // 创建视图
    passwordLoginView = new QtPasswordLoginView();
    verificationLoginView = new QtVerificationLoginView();
    registerView = new QtRegisterView();
    
    // 创建模型
    userModel = new UserModel();
    
    // 创建Presenter
    loginPresenter = new LoginPresenter(
        passwordLoginView, 
        verificationLoginView, 
        registerView, 
        userModel
    );
    
    // 设置导航回调
    passwordLoginView->attachOnSwitchToVerificationClicked([this](){ navigateToVerificationLogin(); });
    passwordLoginView->attachOnRegisterClicked([this](){ navigateToRegister(); });
    verificationLoginView->attachOnSwitchToPasswordLoginClicked([this](){ navigateToPasswordLogin(); });
    registerView->attachOnBackToLoginClicked([this](){ navigateToPasswordLogin(); });
    
    // 初始化活跃视图
    activeView = passwordLoginView;
}

LoginCoordinator::~LoginCoordinator() {
    delete loginPresenter;
    delete userModel;
    delete passwordLoginView;
    delete verificationLoginView;
    delete registerView;
}

void LoginCoordinator::start() {
    // 启动时默认显示密码登录视图
    navigateToPasswordLogin();
}

void LoginCoordinator::navigateToPasswordLogin() {
    if (activeView) {
        activeView->hide();
    }
    passwordLoginView->show();
    activeView = passwordLoginView;
}

void LoginCoordinator::navigateToVerificationLogin() {
    if (activeView) {
        activeView->hide();
    }
    verificationLoginView->show();
    activeView = verificationLoginView;
}

void LoginCoordinator::navigateToRegister() {
    if (activeView) {
        activeView->hide();
    }
    registerView->show();
    activeView = registerView;
} 