#include "QtTransportPanel.h"
#include "QtLayoutUtil.h"
#include <QHBoxLayout>

QtTransportPanel::QtTransportPanel(IPlaybackControl& playback, QWidget* parent)
    : QWidget(parent), playback_control_(playback) {
    setup();
    wire();
}

void QtTransportPanel::setup() {
    auto* layout = new QHBoxLayout(this);

    previous_button_ = new QPushButton("\xe2\x8f\xae", this);
    toggle_button_ = new QPushButton("\xe2\x96\xb6", this);
    toggle_button_->setObjectName("toggle_button");
    next_button_ = new QPushButton("\xe2\x8f\xad", this);

    layout->addWidget(previous_button_);
    layout->addWidget(toggle_button_);
    layout->addWidget(next_button_);
    QtLayoutUtil::center(layout);

    enable(false);
}

void QtTransportPanel::wire() {
    connect(toggle_button_, &QPushButton::clicked, this, [this]() { playback_control_.onToggle(); });
    connect(next_button_, &QPushButton::clicked, this, [this]() { playback_control_.onAdvance(); });
    connect(previous_button_, &QPushButton::clicked, this, [this]() { playback_control_.onRetreat(); });
}

void QtTransportPanel::enable(const bool state) {
    toggle_button_->setEnabled(state);
    next_button_->setEnabled(state);
    previous_button_->setEnabled(state);
}

void QtTransportPanel::toggle(const bool playing) {
    toggle_button_->setText(playing ? "\xe2\x8f\xb8" : "\xe2\x96\xb6");
}