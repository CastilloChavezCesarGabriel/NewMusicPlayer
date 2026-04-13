#include "QtRemoveConnection.h"

QtRemoveConnection::QtRemoveConnection(QtLibraryBar& libraryBar, QtPlaylistDisplay& display) {
    connect(&libraryBar, &QtLibraryBar::removeClicked, &display, &QtPlaylistDisplay::remove);
}