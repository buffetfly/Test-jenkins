#pragma once

#include "Login\View\IPasswordLoginView.h"
#include <QWidget>

namespace Ui {
    class QtPasswordLoginView;
}

class QtPasswordLoginView : public QWidget, public IPasswordLoginView {
    Q_OBJECT

public:
    explicit QtPasswordLoginView(QWidget *parent = nullptr);
    ~QtPasswordLoginView() override;

    // ILoginView接口实现
    void show() override;
    void hide() override;
    void showMessage(const QString& message) override;
    void clearInputs() override;
    
    // IPasswordLoginView接口实现
    QString getUsername() const override;
    QString getPassword() const override;
    void attachOnLoginClicked(std::function<void()> callback) override;
    void attachOnSwitchToVerificationClicked(std::function<void()> callback) override;
    void attachOnRegisterClicked(std::function<void()> callback) override;

private slots:
    void onLoginClicked();
    void onSwitchToVerificationClicked();
    void onRegisterClicked();

private:
    Ui::QtPasswordLoginView *ui;
    std::function<void()> loginCallback;
    std::function<void()> switchToVerificationCallback;
    std::function<void()> registerCallback;
}; 