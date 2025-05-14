#include "LoginPresenterTest.h"
//#include "../../GlobalEncoding.h"
#include <QDir>
#include <QFile>
#include <QDebug>

// 测试初始化和清理方法
void LoginPresenterTest::initTestCase() {
    qDebug() << u8"开始执行测试套件";
    
    // 创建测试用的用户文件目录
    m_testUserFile = QDir::tempPath() + "/test_userdata.txt";
    qDebug() << u8"测试用户文件:" << m_testUserFile;
    
    // 确保开始测试时文件不存在
    QFile file(m_testUserFile);
    if (file.exists()) {
        file.remove();
    }
}

void LoginPresenterTest::cleanupTestCase() {
    qDebug() << u8"测试套件执行完毕";
    
    // 测试结束后删除测试文件
    QFile file(m_testUserFile);
    if (file.exists()) {
        file.remove();
    }
}

void LoginPresenterTest::init() {
    // 每个测试开始前初始化视图和模型
    m_mockPasswordView = new MockPasswordLoginView();
    m_mockVerificationView = new MockVerificationLoginView();
    m_mockRegisterView = new MockRegisterView();
    m_userModel = new UserModel();
    
    // 创建Presenter
    m_presenter = new LoginPresenter(m_mockPasswordView, m_mockVerificationView, m_mockRegisterView, m_userModel);
}

void LoginPresenterTest::cleanup() {
    // 每个测试结束后清理资源
    delete m_presenter;
    delete m_userModel;
    delete m_mockPasswordView;
    delete m_mockVerificationView;
    delete m_mockRegisterView;
    
    // 清理用户文件
    QFile file(m_testUserFile);
    if (file.exists()) {
        file.remove();
    }
}

// 测试用户名密码登录成功
void LoginPresenterTest::testPasswordLoginSuccess() {
    // 准备
    m_userModel->registerUser("test_user", "test_password");
    m_mockPasswordView->setMockUsername("test_user");
    m_mockPasswordView->setMockPassword("test_password");
    
    // 执行
    m_mockPasswordView->triggerLoginClicked();
    
    // 验证
    QStringList messages = m_mockPasswordView->getMessageHistory();
    QVERIFY(!messages.isEmpty());
    QVERIFY(messages.last().contains(u8"登录成功"));
}

// 测试用户名密码登录失败
void LoginPresenterTest::testPasswordLoginFailure() {
    // 准备
    m_userModel->registerUser("test_user", "test_password");
    m_mockPasswordView->setMockUsername("test_user");
    m_mockPasswordView->setMockPassword("wrong_password");
    
    // 执行
    m_mockPasswordView->triggerLoginClicked();
    
    // 验证
    QStringList messages = m_mockPasswordView->getMessageHistory();
    QVERIFY(!messages.isEmpty());
    QVERIFY(messages.last().contains(u8"用户名或密码错误"));
}

// 测试输入为空的情况
void LoginPresenterTest::testPasswordLoginEmpty() {
    // 准备
    m_mockPasswordView->setMockUsername("");
    m_mockPasswordView->setMockPassword("");
    
    // 执行
    m_mockPasswordView->triggerLoginClicked();
    
    // 验证
    QStringList messages = m_mockPasswordView->getMessageHistory();
    QVERIFY(!messages.isEmpty());
    QVERIFY(messages.last().contains(u8"用户名和密码不能为空"));
}

// 测试人机验证成功
void LoginPresenterTest::testVerificationLoginSuccess() {
    // 准备
    m_mockVerificationView->setMockVerificationValue(85); // 大于70，应该通过验证
    
    // 执行
    m_mockVerificationView->triggerVerifyClicked();
    
    // 验证
    QStringList messages = m_mockVerificationView->getMessageHistory();
    QVERIFY(!messages.isEmpty());
    QVERIFY(messages.last().contains(u8"验证成功") || messages.last().contains(u8"登录成功"));
}

// 测试人机验证失败
void LoginPresenterTest::testVerificationLoginFailure() {
    // 准备
    m_mockVerificationView->setMockVerificationValue(50); // 小于70，应该验证失败
    
    // 执行
    m_mockVerificationView->triggerVerifyClicked();
    
    // 验证
    QStringList messages = m_mockVerificationView->getMessageHistory();
    QVERIFY(!messages.isEmpty());
    QVERIFY(messages.last().contains(u8"验证失败"));
}

// 测试注册成功
void LoginPresenterTest::testRegisterSuccess() {
    // 准备
    m_mockRegisterView->setMockUsername("new_user");
    m_mockRegisterView->setMockPassword("new_password");
    m_mockRegisterView->setMockConfirmPassword("new_password");
    
    // 执行
    m_mockRegisterView->triggerRegisterSubmitClicked();
    
    // 验证
    QStringList messages = m_mockRegisterView->getMessageHistory();
    QVERIFY(!messages.isEmpty());
    QVERIFY(messages.last().contains(u8"注册成功"));
    
    // 验证用户是否真的被注册了
    QVERIFY(m_userModel->validateUser("new_user", "new_password"));
}

// 测试注册用户名已存在
void LoginPresenterTest::testRegisterDuplicateUsername() {
    // 准备
    m_userModel->registerUser("existing_user", "test_password");
    m_mockRegisterView->setMockUsername("existing_user");
    m_mockRegisterView->setMockPassword("new_password");
    m_mockRegisterView->setMockConfirmPassword("new_password");
    
    // 执行
    m_mockRegisterView->triggerRegisterSubmitClicked();
    
    // 验证
    QStringList messages = m_mockRegisterView->getMessageHistory();
    QVERIFY(!messages.isEmpty());
    QVERIFY(messages.last().contains(u8"注册失败") || messages.last().contains(u8"用户名可能已存在"));
}

// 测试注册密码不匹配
void LoginPresenterTest::testRegisterPasswordMismatch() {
    // 准备
    m_mockRegisterView->setMockUsername("new_user");
    m_mockRegisterView->setMockPassword("password1");
    m_mockRegisterView->setMockConfirmPassword("password2");
    
    // 执行
    m_mockRegisterView->triggerRegisterSubmitClicked();
    
    // 验证
    QStringList messages = m_mockRegisterView->getMessageHistory();
    QVERIFY(!messages.isEmpty());
    QVERIFY(messages.last().contains(u8"两次输入的密码不一致"));
}

// 测试注册密码太短
void LoginPresenterTest::testRegisterShortPassword() {
    // 准备
    m_mockRegisterView->setMockUsername("new_user");
    m_mockRegisterView->setMockPassword("12345");
    m_mockRegisterView->setMockConfirmPassword("12345");
    
    // 执行
    m_mockRegisterView->triggerRegisterSubmitClicked();
    
    // 验证
    QStringList messages = m_mockRegisterView->getMessageHistory();
    QVERIFY(!messages.isEmpty());
    QVERIFY(messages.last().contains(u8"密码长度必须至少为6个字符"));
}

// 测试注册字段为空
void LoginPresenterTest::testRegisterEmptyFields() {
    // 准备
    m_mockRegisterView->setMockUsername("");
    m_mockRegisterView->setMockPassword("password");
    m_mockRegisterView->setMockConfirmPassword("password");
    
    // 执行
    m_mockRegisterView->triggerRegisterSubmitClicked();
    
    // 验证
    QStringList messages = m_mockRegisterView->getMessageHistory();
    QVERIFY(!messages.isEmpty());
    QVERIFY(messages.last().contains(u8"所有字段都必须填写"));
}

// 测试主函数
// 如果需要使用QTEST_MAIN，请注释掉下面的QTEST_MAIN(LoginPresenterTest)
// 如果需要使用QTEST_MAIN，请包含qtest.h，并取消下面的QTEST_MAIN(LoginPresenterTest)注释
// QTEST_MAIN(LoginPresenterTest)