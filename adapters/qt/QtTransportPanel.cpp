#include "QtTransportPanel.h"
#include "QtLayoutUtil.h"
#include <QHBoxLayout>

QtTransportPanel::QtTransportPanel(IPlaybackControl& playback, QWidget* parent)
    : QWidget(parent), playback_(playback) {
    setup();
    wire();
}

void QtTransportPanel::setup() {
    auto* layout = new QHBoxLayout(this);

    previous_ = new QPushButton("\xe2\x8f\xae", this);
    toggle_ = new QPushButton("\xe2\x96\xb6", this);
    toggle_->setObjectName("toggle_button");
    next_ = new QPushButton("\xe2\x8f\xad", this);

    layout->addWidget(previous_);
    layout->addWidget(toggle_);
    layout->addWidget(next_);
    QtLayoutUtil::center(layout);

    enable(false);
}

void QtTransportPanel::wire() {
    connect(toggle_, &QPushButton::clicked, this, [this]() { playback_.onToggle(); });
    connect(next_, &QPushButton::clicked, this, [this]() { playback_.onAdvance(); });
    connect(previous_, &QPushButton::clicked, this, [this]() { playback_.onRetreat(); });
}

void QtTransportPanel::enable(const bool state) {
    toggle_->setEnabled(state);
    next_->setEnabled(state);
    previous_->setEnabled(state);
}

void QtTransportPanel::toggle(const bool playing) {
    toggle_->setText(playing ? "\xe2\x8f\xb8" : "\xe2\x96\xb6");
}
