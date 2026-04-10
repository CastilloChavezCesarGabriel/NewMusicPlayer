#include "QtVolumePanel.h"
#include <QHBoxLayout>

QtVolumePanel::QtVolumePanel(IPlaybackControl& playback, QWidget* parent)
    : QWidget(parent), playback_(playback) {

    auto* layout = new QHBoxLayout(this);

    label_ = new QLabel("50%", this);
    label_->setObjectName("volume_label");
    slider_ = new QSlider(Qt::Horizontal, this);
    slider_->setRange(0, 100);
    slider_->setValue(50);

    layout->addWidget(label_);
    layout->addWidget(slider_);

    connect(slider_, &QSlider::valueChanged, this, [this](const int value) {
        adjust(value);
        playback_.onAdjust(value);
    });
}

void QtVolumePanel::adjust(const int volume) const {
    label_->setText(QString("%1%").arg(volume));
}
