#include "QtToggleConnection.h"

QtToggleConnection::QtToggleConnection(QtAudioEngine& audio, IPlaybackDisplay& display)
    : playback_display_(display) {
    connect(&audio, &QtAudioEngine::toggleRequested, this, &QtToggleConnection::relay);
}

void QtToggleConnection::relay(const bool playing) const {
    playback_display_.toggle(playing);
}