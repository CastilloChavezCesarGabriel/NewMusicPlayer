#include "QtRemoveConnection.h"

QtRemoveConnection::QtRemoveConnection(QtToolbar& toolbar, QtPlaylistDisplay& display) {
    connect(&toolbar, &QtToolbar::removeClicked, &display, &QtPlaylistDisplay::remove);
}