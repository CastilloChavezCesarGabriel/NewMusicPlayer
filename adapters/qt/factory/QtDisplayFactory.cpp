#include "QtDisplayFactory.h"

QtPlaylistDisplay* QtDisplayFactory::createDisplay(IPlaybackControl& playback, ILibraryControl& library, QWidget* parent) {
    return new QtPlaylistDisplay(playback, library, parent);
}

QtSortHeader* QtDisplayFactory::createSortHeader(QWidget* parent) {
    return new QtSortHeader(parent);
}

QtSearchOverlay* QtDisplayFactory::createSearchOverlay(QWidget* parent) {
    return new QtSearchOverlay(parent);
}

QtLibraryBar* QtDisplayFactory::createLibraryBar(ILibraryControl& library, QWidget* parent) {
    return new QtLibraryBar(library, parent);
}
