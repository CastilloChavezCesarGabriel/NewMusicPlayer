#include "QtShuffleButton.h"
#include "../icon/QtIconPainter.h"
#include "../QtLayoutUtil.h"
#include <QHBoxLayout>

QtShuffleButton::QtShuffleButton(IOrderControl& order, QWidget* parent)
    : QWidget(parent), order_(order) {
    setup();
    wire();
}

void QtShuffleButton::setup() {
    auto* layout = new QHBoxLayout(this);
    button_ = new QPushButton(this);
    button_->setObjectName("shuffle_button");
    button_->setIconSize(QSize(16, 20));
    layout->addWidget(button_);
    QtLayoutUtil::flatten(layout);
    QtIconPainter::paint(button_, "/resources/icons/shuffle.png");
    enable(false);
}

void QtShuffleButton::wire() {
    connect(button_, &QPushButton::clicked, this, [this]() { order_.onShuffle(); });
}

void QtShuffleButton::enable(const bool state) {
    button_->setEnabled(state);
}