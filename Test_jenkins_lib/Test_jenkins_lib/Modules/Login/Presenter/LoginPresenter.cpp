#include "LoginPresenter.h"
#include "../Model/UserModel.h"
#include "../View/IPasswordLoginView.h"
#include "../View/IVerificationLoginView.h"
#include "../View/IRegisterView.h"

LoginPresenter::LoginPresenter(
    IPasswordLoginView* passwordView, 
    IVerificationLoginView* verificationView,
    IRegisterView* registerView, 
    UserModel* model
) : passwordLoginView(passwordView), 
    verificationLoginView(verificationView),
    registerView(registerView),
    userModel(model) {
    
    // 连接事件处理
    passwordLoginView->attachOnLoginClicked([this](){ handlePasswordLogin(); });
    verificationLoginView->attachOnVerifyClicked([this](){ handleVerificationLogin(); });
    registerView->attachOnRegisterSubmitClicked([this](){ handleRegister(); });
}

LoginPresenter::~LoginPresenter() {
    // Presenter不负责视图和模型的生命周期
}

void LoginPresenter::handlePasswordLogin() {
    if (!validatePasswordLogin()) {
        return;
    }
    
    QString username = passwordLoginView->getUsername();
    QString password = passwordLoginView->getPassword();
    
    if (userModel->validateUser(username, password)) {
        passwordLoginView->showMessage(u8"登录成功！");
        passwordLoginView->clearInputs();
        // 这里可以进行登录成功后的处理
    } else {
        passwordLoginView->showMessage(u8"用户名或密码错误！");
    }
}

void LoginPresenter::handleVerificationLogin() {
    if (!validateVerification()) {
        return;
    }
    
    verificationLoginView->showMessage(u8"验证成功，登录成功！");
    verificationLoginView->clearInputs();
    // 这里可以进行登录成功后的处理
}

void LoginPresenter::handleRegister() {
    if (!validateRegistration()) {
        return;
    }
    
    QString username = registerView->getUsername();
    QString password = registerView->getPassword();
    
    if (userModel->registerUser(username, password)) {
        registerView->showMessage(u8"注册成功！");
        registerView->clearInputs();
        // 注册成功后的处理，通常是导航回登录界面
    } else {
        registerView->showMessage(u8"注册失败，用户名可能已存在！");
    }
}

bool LoginPresenter::validatePasswordLogin() {
    QString username = passwordLoginView->getUsername();
    QString password = passwordLoginView->getPassword();
    
    if (username.isEmpty() || password.isEmpty()) {
        passwordLoginView->showMessage(u8"用户名和密码不能为空！");
        return false;
    }
    
    return true;
}

bool LoginPresenter::validateRegistration() {
    QString username = registerView->getUsername();
    QString password = registerView->getPassword();
    QString confirmPassword = registerView->getConfirmPassword();
    
    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        registerView->showMessage(u8"所有字段都必须填写！");
        return false;
    }
    
    if (password != confirmPassword) {
        registerView->showMessage(u8"两次输入的密码不一致！");
        return false;
    }
    
    if (password.length() < 6) {
        registerView->showMessage(u8"密码长度必须至少为6个字符！");
        return false;
    }
    
    return true;
}

bool LoginPresenter::validateVerification() {
    int sliderValue = verificationLoginView->getVerificationValue();
    // 这里假设滑动到70以上就算验证成功
    return sliderValue >= 70;
} 
