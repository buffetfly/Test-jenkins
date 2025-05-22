#pragma once

#include "Login\View\IRegisterView.h"
#include <QWidget>

namespace Ui {
    class QtRegisterView;
}

class QtRegisterView : public QWidget, public IRegisterView {
    Q_OBJECT

public:
    explicit QtRegisterView(QWidget *parent = nullptr);
    ~QtRegisterView() override;

    // ILoginView接口实现
    void show() override;
    void hide() override;
    void showMessage(const QString& message) override;
    void clearInputs() override;
    
    // IRegisterView接口实现
    QString getUsername() const override;
    QString getPassword() const override;
    QString getConfirmPassword() const override;
    void attachOnRegisterSubmitClicked(std::function<void()> callback) override;
    void attachOnBackToLoginClicked(std::function<void()> callback) override;

private slots:
    void onRegisterSubmitClicked();
    void onBackToLoginClicked();

private:
    Ui::QtRegisterView *ui;
    std::function<void()> registerSubmitCallback;
    std::function<void()> backToLoginCallback;
}; 