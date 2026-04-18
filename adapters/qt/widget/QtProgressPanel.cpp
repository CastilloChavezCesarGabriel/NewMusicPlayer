#include "QtProgressPanel.h"
#include <QHBoxLayout>

QtProgressPanel::QtProgressPanel(QMediaPlayer& media, QWidget* parent)
    : QWidget(parent), media_(media) {
    setup();
    wire();
}

void QtProgressPanel::setup() {
    auto* layout = new QHBoxLayout(this);

    elapsed_time_ = new QLabel("0:00", this);
    elapsed_time_->setObjectName("elapsed_time");
    progress_bar_ = new QSlider(Qt::Horizontal, this);
    progress_bar_->setMinimum(0);
    total_time_ = new QLabel("0:00", this);
    total_time_->setObjectName("total_time");

    layout->addWidget(elapsed_time_);
    layout->addWidget(progress_bar_);
    layout->addWidget(total_time_);
}

void QtProgressPanel::wire() {
    connect(&media_, &QMediaPlayer::positionChanged, this,
            [this](const qint64 position) { reflect(position); });
    connect(&media_, &QMediaPlayer::durationChanged, this,
            [this](const qint64 duration) { resize(duration); });
    connect(progress_bar_, &QSlider::sliderReleased, this,
            [this] { seek(); });
}

void QtProgressPanel::reflect(const qint64 position) const {
    if (!progress_bar_->isSliderDown()) {
        progress_bar_->setValue(static_cast<int>(position));
    }
    elapsed_time_->setText(format(position));
}

void QtProgressPanel::resize(const qint64 duration) const {
    progress_bar_->setMaximum(static_cast<int>(duration));
    total_time_->setText(format(duration));
}

void QtProgressPanel::seek() const {
    media_.setPosition(progress_bar_->value());
}

void QtProgressPanel::enable(const bool state) const {
    progress_bar_->setEnabled(state);
}

QString QtProgressPanel::format(const qint64 milliseconds) {
    const int seconds = static_cast<int>(milliseconds / 1000);
    const int minutes = seconds / 60;
    const int remaining = seconds % 60;
    return QString("%1:%2").arg(minutes).arg(remaining, 2, 10, QChar('0'));
}