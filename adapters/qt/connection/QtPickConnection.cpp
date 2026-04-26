#include "QtPickConnection.h"

QtPickConnection::QtPickConnection(QtSearchOverlay& overlay, ISearchInput& display)
    : display_control_(display) {
    connect(&overlay, &QtSearchOverlay::selectRequested, this, &QtPickConnection::relay);
}

void QtPickConnection::relay(const std::string& name) const {
    display_control_.onPick(name);
}