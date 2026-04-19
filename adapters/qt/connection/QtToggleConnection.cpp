#include "QtToggleConnection.h"

QtToggleConnection::QtToggleConnection(QtAudioEngine& audio, QtTransportPanel& transport)
    : transport_(transport) {
    connect(&audio, &QtAudioEngine::toggleRequested, this, &QtToggleConnection::relay);
}

void QtToggleConnection::relay(const bool playing) const {
    transport_.toggle(playing);
}