#include "QtArrangementPanel.h"
#include "QtLayoutUtil.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QStyle>
#include <filesystem>

static std::string resolve(const std::string& path) {
    return std::filesystem::current_path().string() + path;
}

QtArrangementPanel::QtArrangementPanel(IArrangementControl& arrangement, QWidget* parent)
    : QWidget(parent), arrangement_(arrangement) {
    setup();
    wire();
}

void QtArrangementPanel::setup() {
    auto* layout = new QHBoxLayout(this);

    shuffle_ = new QPushButton(this);
    shuffle_->setObjectName("shuffle_button");
    shuffle_->setIconSize(QSize(16, 20));

    repeat_ = new QPushButton(this);
    repeat_->setObjectName("repeat_button");
    repeat_->setIconSize(QSize(16, 16));

    layout->addWidget(shuffle_);
    layout->addWidget(repeat_);
    QtLayoutUtil::center(layout);

    paint(shuffle_, "/resources/icons/shuffle.png");
    paint(repeat_, "/resources/icons/repeat.png");
    enable(false);
}

void QtArrangementPanel::wire() {
    connect(shuffle_, &QPushButton::clicked, this, [this]() { arrangement_.onShuffle(); });
    connect(repeat_, &QPushButton::clicked, this, [this]() { arrangement_.onRepeat(); });
}

void QtArrangementPanel::enable(const bool state) {
    shuffle_->setEnabled(state);
    repeat_->setEnabled(state);
}

void QtArrangementPanel::repeat(const int mode) {
    paint(repeat_, mode == 1 ? "/resources/icons/repeat_one.png" : "/resources/icons/repeat.png");
    repeat_->setProperty("active", mode == 2);
    repeat_->style()->unpolish(repeat_);
    repeat_->style()->polish(repeat_);
}

void QtArrangementPanel::paint(QPushButton* button, const std::string& path) {
    QPixmap pixmap(QString::fromStdString(resolve(path)));
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), Qt::white);
    painter.end();
    button->setIcon(QIcon(pixmap));
    button->setText("");
}
