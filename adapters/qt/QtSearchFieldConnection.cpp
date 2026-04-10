#include "QtSearchFieldConnection.h"

QtSearchFieldConnection::QtSearchFieldConnection(QtSearchField& field, IDisplayControl& display)
    : display_control_(display) {
    connect(&field, &QtSearchField::searchRequested, this, &QtSearchFieldConnection::relay);
}

void QtSearchFieldConnection::relay(const std::string& query) const {
    display_control_.onSearch(query);
}