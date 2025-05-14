#pragma once

#include "IVerificationLoginView.h"
#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QLabel>

namespace Ui {
    class QtVerificationLoginView;
}

class QtVerificationLoginView : public QWidget, public IVerificationLoginView {
    Q_OBJECT

public:
    explicit QtVerificationLoginView(QWidget *parent = nullptr);
    ~QtVerificationLoginView() override;

    // ILoginView接口实现
    void show() override;
    void hide() override;
    void showMessage(const QString& message) override;
    void clearInputs() override;
    
    // IVerificationLoginView接口实现
    int getVerificationValue() const override;
    void attachOnVerifyClicked(std::function<void()> callback) override;
    void attachOnSwitchToPasswordLoginClicked(std::function<void()> callback) override;

    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void onSwitchToPasswordLoginClicked();
    void onSliderValueChanged(int value);
    void onSliderReleased();

private:
    Ui::QtVerificationLoginView *ui;
    std::function<void()> verifyCallback;
    std::function<void()> switchToPasswordLoginCallback;
    
    QPixmap originalImage;    // 原始图片
    QPixmap puzzleImage;      // 完整拼图
    QPixmap puzzlePiece;      // 拼图碎片
    QLabel* puzzlePieceLabel; // 拼图碎片标签
    
    int puzzleX;              // 拼图碎片的目标X坐标
    int puzzleHeight;         // 拼图的高度
    int pieceWidth;           // 拼图碎片的宽度
    int pieceHeight;          // 拼图碎片的高度
    
    void loadVerificationImage();
    void setupPuzzle();
    void updatePuzzlePiecePosition(int sliderValue);
    bool isPuzzleCorrect() const;
    QPixmap createPuzzlePiece(const QPixmap& source, QRect rect);
}; 