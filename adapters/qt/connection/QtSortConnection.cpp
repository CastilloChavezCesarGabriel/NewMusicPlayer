#include "QtSortConnection.h"

QtSortConnection::QtSortConnection(QtSortHeader& header, IArrangementControl& arrangement)
    : arrangement_control_(arrangement) {
    connect(&header, &QtSortHeader::clickRequested, this, &QtSortConnection::relay);
}

void QtSortConnection::relay() const {
    arrangement_control_.onSort();
}