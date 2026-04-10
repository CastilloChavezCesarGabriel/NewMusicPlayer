#include "QtArrangementPanel.h"
#include "QtIconPainter.h"
#include "QtLayoutUtil.h"
#include <QHBoxLayout>
#include <QStyle>

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

    QtIconPainter::paint(shuffle_, "/resources/icons/shuffle.png");
    QtIconPainter::paint(repeat_, "/resources/icons/repeat.png");
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
    QtIconPainter::paint(repeat_, mode == 1 ? "/resources/icons/repeat_one.png" : "/resources/icons/repeat.png");
    repeat_->setProperty("active", mode == 2);
    repeat_->style()->unpolish(repeat_);
    repeat_->style()->polish(repeat_);
}