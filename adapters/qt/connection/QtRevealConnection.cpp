#include "QtRevealConnection.h"

QtRevealConnection::QtRevealConnection(QtAudioEngine& audio, IToolbarDisplay& toolbar)
    : toolbar_display_(toolbar) {
    connect(&audio, &QtAudioEngine::revealRequested, this, &QtRevealConnection::relay);
}

void QtRevealConnection::relay() const {
    toolbar_display_.reveal(true);
}