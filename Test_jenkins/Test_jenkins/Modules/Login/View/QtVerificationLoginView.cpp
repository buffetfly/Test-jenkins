#include "QtVerificationLoginView.h"
#include "ui_QtVerificationLoginView.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QDebug>

QtVerificationLoginView::QtVerificationLoginView(QWidget* parent)
    : QWidget(parent), ui(new Ui::QtVerificationLoginView), 
    puzzlePieceLabel(nullptr), puzzleX(0), puzzleHeight(0), 
    pieceWidth(0), pieceHeight(0) {
    ui->setupUi(this);

    // 加载验证图片
    loadVerificationImage();

    // 连接信号和槽
    connect(ui->backToPasswordButton, &QPushButton::clicked, this, &QtVerificationLoginView::onSwitchToPasswordLoginClicked);
    connect(ui->verificationSlider, &QSlider::valueChanged, this, &QtVerificationLoginView::onSliderValueChanged);
    connect(ui->verificationSlider, &QSlider::sliderReleased, this, &QtVerificationLoginView::onSliderReleased);

    // 安装事件过滤器，用于处理窗口大小变化
    ui->verificationImageLabel->installEventFilter(this);
}

QtVerificationLoginView::~QtVerificationLoginView() {
    if (puzzlePieceLabel) {
        delete puzzlePieceLabel;
    }
    delete ui;
}

bool QtVerificationLoginView::eventFilter(QObject* watched, QEvent* event) {
    if (watched == ui->verificationImageLabel && event->type() == QEvent::Resize) {
        loadVerificationImage();
    }
    return QWidget::eventFilter(watched, event);
}

void QtVerificationLoginView::loadVerificationImage() {
    // 尝试加载资源中的图片
    originalImage = QPixmap(":/qrc/pic.png");
    if (originalImage.isNull()) {
        // 如果没有图片资源，使用纯色图片
        originalImage = QPixmap(ui->verificationImageLabel->width(), ui->verificationImageLabel->height());
        originalImage.fill(Qt::lightGray);
        
        // 在纯色图片上绘制一些内容，以便进行拼图验证
        QPainter painter(&originalImage);
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 20));
        painter.drawText(originalImage.rect(), Qt::AlignCenter, "验证图片");
        
        // 绘制一些随机图形
        for (int i = 0; i < 10; ++i) {
            int x = QRandomGenerator::global()->bounded(originalImage.width());
            int y = QRandomGenerator::global()->bounded(originalImage.height());
            int width = QRandomGenerator::global()->bounded(50, 100);
            int height = QRandomGenerator::global()->bounded(20, 60);
            
            painter.setPen(QColor(
                QRandomGenerator::global()->bounded(256),
                QRandomGenerator::global()->bounded(256),
                QRandomGenerator::global()->bounded(256)
            ));
            painter.drawEllipse(x, y, width, height);
        }
    }
    
    // 调整图片大小以适应标签
    int labelWidth = ui->verificationImageLabel->width();
    int labelHeight = ui->verificationImageLabel->height();
    
    // 确保图片填满标签区域
    originalImage = originalImage.scaled(
        labelWidth,
        labelHeight,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );
    
    // 如果图片比标签小，创建一个新的背景图片并将原图居中放置
    if (originalImage.width() < labelWidth || originalImage.height() < labelHeight) {
        QPixmap background(labelWidth, labelHeight);
        background.fill(Qt::lightGray);
        
        QPainter painter(&background);
        int x = (labelWidth - originalImage.width()) / 2;
        int y = (labelHeight - originalImage.height()) / 2;
        painter.drawPixmap(x, y, originalImage);
        originalImage = background;
    }
    
    // 设置拼图
    setupPuzzle();
}

void QtVerificationLoginView::setupPuzzle() {
    // 清除旧的拼图碎片
    if (puzzlePieceLabel) {
        puzzlePieceLabel->hide();
        delete puzzlePieceLabel;
        puzzlePieceLabel = nullptr;
    }
    
    // 获取验证图片的尺寸
    int imageWidth = originalImage.width();
    puzzleHeight = originalImage.height();
    
    // 拼图碎片尺寸 - 确保合理比例
    pieceWidth = qMin(imageWidth / 6, 60);  // 拼图碎片宽度为图片宽度的1/6，最大60像素
    pieceHeight = qMin(puzzleHeight / 3, 40); // 拼图碎片高度，最大40像素
    
    // 随机选择拼图碎片的X坐标位置
    // 确保缺口位置在合理范围内
    int margin = 10; // 边缘留白
    int minX = margin;
    int maxX = imageWidth - pieceWidth - margin;
    
    puzzleX = QRandomGenerator::global()->bounded(minX, maxX);
    
    // 随机选择拼图碎片的Y坐标位置
    // 确保缺口不会太靠近上下边缘
    int minY = margin;
    int maxY = puzzleHeight - pieceHeight - margin;
    
    int puzzleY = QRandomGenerator::global()->bounded(minY, maxY);
    
    // 创建带缺口的拼图图片
    puzzleImage = QPixmap(originalImage);
    
    QPainter painter(&puzzleImage);
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.fillRect(puzzleX, puzzleY, pieceWidth, pieceHeight, Qt::white);
    
    // 创建拼图碎片
    QRect pieceRect(puzzleX, puzzleY, pieceWidth, pieceHeight);
    puzzlePiece = createPuzzlePiece(originalImage, pieceRect);
    
    // 设置显示的拼图图片（带缺口的）
    ui->verificationImageLabel->setPixmap(puzzleImage);
    
    // 创建拼图碎片标签
    puzzlePieceLabel = new QLabel(ui->verificationImageLabel);
    puzzlePieceLabel->setPixmap(puzzlePiece);
    
    // 将拼图碎片放在左侧
    puzzlePieceLabel->setGeometry(0, puzzleY, pieceWidth, pieceHeight);
    puzzlePieceLabel->show();
    
    // 重置滑块位置
    ui->verificationSlider->blockSignals(true);
    ui->verificationSlider->setValue(0);
    ui->verificationSlider->blockSignals(false);
    
    // 初始化拼图碎片位置
    updatePuzzlePiecePosition(0);
}

QPixmap QtVerificationLoginView::createPuzzlePiece(const QPixmap& source, QRect rect) {
    // 从原图中提取拼图碎片
    QPixmap piece = source.copy(rect);
    
    // 给拼图碎片添加边框和阴影效果
    QPixmap enhancedPiece(piece.size());
    enhancedPiece.fill(Qt::transparent);
    
    QPainter painter(&enhancedPiece);
    
    // 绘制阴影
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 50));
    painter.drawRect(3, 3, piece.width() - 3, piece.height() - 3);
    
    // 绘制碎片
    painter.drawPixmap(0, 0, piece);
    
    // 绘制边框
    painter.setPen(QPen(QColor(255, 255, 255, 180), 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(0, 0, piece.width() - 1, piece.height() - 1);
    
    return enhancedPiece;
}

void QtVerificationLoginView::updatePuzzlePiecePosition(int sliderValue) {
    if (!puzzlePieceLabel) return;
    
    // 计算拼图碎片的X坐标
    // 允许滑块超过缺口位置，最大可移动到图片右边缘
    int imageWidth = ui->verificationImageLabel->width();
    int maxX = imageWidth - pieceWidth;
    
    double ratio = static_cast<double>(sliderValue) / ui->verificationSlider->maximum();
    int x = static_cast<int>(ratio * maxX);
    
    // 限制碎片的位置，确保不会超出图片边界
    x = qMax(0, qMin(x, maxX));
    
    // 保持Y坐标不变，仅更新X坐标
    int currentY = puzzlePieceLabel->y();
    puzzlePieceLabel->setGeometry(x, currentY, pieceWidth, pieceHeight);
}

bool QtVerificationLoginView::isPuzzleCorrect() const {
    if (!puzzlePieceLabel) return false;
    
    // 获取当前拼图碎片的位置
    int currentX = puzzlePieceLabel->x();
    
    // 检查拼图碎片是否与缺口位置匹配
    // 允许5像素的误差
    return qAbs(currentX - puzzleX) <= 5;
}

int QtVerificationLoginView::getVerificationValue() const {
    // 如果拼图正确，则返回100（满分），否则返回当前滑块值
    return isPuzzleCorrect() ? 100 : ui->verificationSlider->value();
}

void QtVerificationLoginView::showMessage(const QString& message) {
    QMessageBox::information(this, u8"提示", message);
}

void QtVerificationLoginView::clearInputs() {
    ui->verificationSlider->setValue(0);
    // 重新设置拼图
    setupPuzzle();
}

void QtVerificationLoginView::show() {
    QWidget::show();
    // 每次显示时重新设置拼图
    loadVerificationImage();
}

void QtVerificationLoginView::hide() {
    QWidget::hide();
}

void QtVerificationLoginView::attachOnVerifyClicked(std::function<void()> callback) {
    verifyCallback = callback;
}

void QtVerificationLoginView::attachOnSwitchToPasswordLoginClicked(std::function<void()> callback) {
    switchToPasswordLoginCallback = callback;
}

void QtVerificationLoginView::onSwitchToPasswordLoginClicked() {
    if (switchToPasswordLoginCallback) {
        switchToPasswordLoginCallback();
    }
}

void QtVerificationLoginView::onSliderValueChanged(int value) {
    // 更新拼图碎片位置
    updatePuzzlePiecePosition(value);
}

void QtVerificationLoginView::onSliderReleased() {
    // 验证拼图是否正确
    if (isPuzzleCorrect()) {
        if (verifyCallback) {
            verifyCallback();
        }
    } else {
        showMessage(u8"验证失败，请重新尝试。");
        // 重新设置拼图
        setupPuzzle();
    }
}