#include "QtEndConnection.h"

QtEndConnection::QtEndConnection(QtAudioEngine& audio, IAudioControl& playback)
    : playback_control_(playback) {
    connect(&audio, &QtAudioEngine::endRequested, this, &QtEndConnection::relay);
}

void QtEndConnection::relay() const {
    playback_control_.onEnd();
}