#include "QtRevealConnection.h"

QtRevealConnection::QtRevealConnection(QtAdTimer& timer, IToolbarDisplay& toolbar)
    : toolbar_display_(toolbar) {
    connect(&timer, &QtAdTimer::revealRequested, this, &QtRevealConnection::relay);
}

void QtRevealConnection::relay() const {
    toolbar_display_.reveal(true);
}