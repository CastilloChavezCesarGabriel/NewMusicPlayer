#include "QtSkipButton.h"
#include "../QtLayoutUtil.h"
#include <QHBoxLayout>

QtSkipButton::QtSkipButton(IPlaybackControl& playback, QWidget* parent)
    : QWidget(parent), playback_control_(playback) {
    setup();
    wire();
}

void QtSkipButton::setup() {
    auto* layout = new QHBoxLayout(this);
    button_ = new QPushButton("\xe2\x8f\xad", this);
    button_->setObjectName("skip_button");
    button_->setVisible(false);
    layout->addWidget(button_);
    QtLayoutUtil::flatten(layout);
}

void QtSkipButton::wire() {
    connect(button_, &QPushButton::clicked, this, [this]() { playback_control_.onSkip(); });
}

void QtSkipButton::enable(const bool state) {
    button_->setEnabled(state);
}

void QtSkipButton::reveal(const bool visible) {
    button_->setVisible(visible);
}
