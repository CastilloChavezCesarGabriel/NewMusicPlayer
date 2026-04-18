#include "QtVolumePanel.h"
#include <QHBoxLayout>

QtVolumePanel::QtVolumePanel(IAudioControl& playback, QWidget* parent)
    : QWidget(parent), playback_control_(playback) {

    auto* layout = new QHBoxLayout(this);

    label_ = new QLabel("50%", this);
    label_->setObjectName("volume_label");
    slider_ = new QSlider(Qt::Horizontal, this);
    slider_->setRange(0, 100);
    slider_->setValue(50);

    layout->addWidget(label_);
    layout->addWidget(slider_);

    connect(slider_, &QSlider::valueChanged, this, [this](const int value) { slide(value); });
}

void QtVolumePanel::slide(const int volume) const {
    adjust(volume);
    playback_control_.onAdjust(volume);
}

void QtVolumePanel::adjust(const int volume) const {
    label_->setText(QString("%1%").arg(volume));
}