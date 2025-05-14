 #pragma once

#include <QObject>
#include <QtTest/QtTest>
#include "../../Modules/Login/Presenter/LoginPresenter.h"
#include "MockPasswordLoginView.h"
#include "MockVerificationLoginView.h"
#include "MockRegisterView.h"
#include "../../Modules/Login/Model/UserModel.h"

class LoginPresenterTest : public QObject {
    Q_OBJECT

private slots:
    // 初始化和清理
    void initTestCase();     // 在第一个测试函数执行前调用
    void cleanupTestCase();  // 在最后一个测试函数执行后调用
    void init();             // 在每个测试函数执行前调用
    void cleanup();          // 在每个测试函数执行后调用
    
    // 测试函数
    void testPasswordLoginSuccess();
    void testPasswordLoginFailure();
    void testPasswordLoginEmpty();
    
    void testVerificationLoginSuccess();
    void testVerificationLoginFailure();
    
    void testRegisterSuccess();
    void testRegisterDuplicateUsername();
    void testRegisterPasswordMismatch();
    void testRegisterShortPassword();
    void testRegisterEmptyFields();

private:
    QString m_testUserFile;
    MockPasswordLoginView* m_mockPasswordView;
    MockVerificationLoginView* m_mockVerificationView;
    MockRegisterView* m_mockRegisterView;
    UserModel* m_userModel;
    LoginPresenter* m_presenter;
};