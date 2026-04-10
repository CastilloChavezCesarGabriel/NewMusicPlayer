#include "QtClearConnection.h"

QtClearConnection::QtClearConnection(QtSearchOverlay& overlay, QtSearchField& field)
    : search_field_(field) {
    connect(&overlay, &QtSearchOverlay::selectRequested, this, &QtClearConnection::relay);
}

void QtClearConnection::relay() const {
    search_field_.clear();
}