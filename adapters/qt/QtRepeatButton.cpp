#include "QtRepeatButton.h"
#include "QtIconPainter.h"
#include "QtLayoutUtil.h"
#include <QHBoxLayout>
#include <QStyle>

QtRepeatButton::QtRepeatButton(IArrangementControl& arrangement, QWidget* parent)
    : QWidget(parent), arrangement_(arrangement) {
    setup();
    wire();
}

void QtRepeatButton::setup() {
    auto* layout = new QHBoxLayout(this);
    button_ = new QPushButton(this);
    button_->setObjectName("repeat_button");
    button_->setIconSize(QSize(16, 16));
    layout->addWidget(button_);
    QtLayoutUtil::flatten(layout);
    QtIconPainter::paint(button_, "/resources/icons/repeat.png");
    enable(false);
}

void QtRepeatButton::wire() {
    connect(button_, &QPushButton::clicked, this, [this]() { arrangement_.onRepeat(); });
}

void QtRepeatButton::enable(const bool state) {
    button_->setEnabled(state);
}

void QtRepeatButton::repeat(const int mode) {
    QtIconPainter::paint(button_, mode == 1 ? "/resources/icons/repeat_one.png" : "/resources/icons/repeat.png");
    button_->setProperty("active", mode == 2);
    button_->style()->unpolish(button_);
    button_->style()->polish(button_);
}
