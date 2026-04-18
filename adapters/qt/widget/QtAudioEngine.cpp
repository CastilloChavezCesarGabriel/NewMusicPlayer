#include "QtAudioEngine.h"
#include <QMediaDevices>
#include "../QtLayoutUtil.h"
#include <QVBoxLayout>
#include <QAudioDevice>
#include <QUrl>

QtAudioEngine::QtAudioEngine(QWidget* parent) : QWidget(parent) {
    setup();
    wire();
    monitor();
}

void QtAudioEngine::setup() {
    media_player_ = new QMediaPlayer(this);
    audio_output_ = new QAudioOutput(this);
    audio_output_->setVolume(0.5);
    media_player_->setAudioOutput(audio_output_);

    progress_bar_ = new QtProgressPanel(*media_player_, this);

    auto* layout = new QVBoxLayout(this);
    QtLayoutUtil::flatten(layout);
    layout->addWidget(progress_bar_);
}

void QtAudioEngine::wire() {
    connect(media_player_, &QMediaPlayer::mediaStatusChanged, this,
            [this](const QMediaPlayer::MediaStatus status) { detect(status); });
    connect(media_player_, &QMediaPlayer::playbackStateChanged, this,
            [this](const QMediaPlayer::PlaybackState state) { announce(state); });
}

void QtAudioEngine::monitor() {
    const auto* devices = new QMediaDevices(this);
    connect(devices, &QMediaDevices::audioOutputsChanged, this, [this] { route(); });
}

void QtAudioEngine::detect(const QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        emit endRequested();
    }
}

void QtAudioEngine::announce(const QMediaPlayer::PlaybackState state) {
    emit toggleRequested(state == QMediaPlayer::PlayingState);
}

void QtAudioEngine::route() const {
    audio_output_->setDevice(QMediaDevices::defaultAudioOutput());
}

void QtAudioEngine::start() const {
    media_player_->play();
}

void QtAudioEngine::play(const std::string& path) {
    media_player_->stop();
    media_player_->setSource(QUrl::fromLocalFile(QString::fromStdString(path)));
    start();
}

void QtAudioEngine::resume() {
    start();
}

void QtAudioEngine::pause() {
    media_player_->pause();
}

void QtAudioEngine::stop() {
    media_player_->stop();
}

void QtAudioEngine::adjust(const int volume) {
    audio_output_->setVolume(volume / 100.0);
}

void QtAudioEngine::enable(const bool state) {
    progress_bar_->enable(state);
}