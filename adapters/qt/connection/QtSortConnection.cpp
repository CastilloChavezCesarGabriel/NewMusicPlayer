#include "QtSortConnection.h"

QtSortConnection::QtSortConnection(QtSortHeader& header, IOrderControl& order)
    : order_control_(order) {
    connect(&header, &QtSortHeader::clickRequested, this, &QtSortConnection::relay);
}

void QtSortConnection::relay() const {
    order_control_.onSort();
}