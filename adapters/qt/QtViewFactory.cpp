#include "QtViewFactory.h"

QtAudioEngine* QtViewFactory::createAudio(QWidget* parent) {
    return new QtAudioEngine(parent);
}

QtPlaylistDisplay* QtViewFactory::createDisplay(IPlaybackControl& playback, ILibraryControl& library, QWidget* parent) {
    return new QtPlaylistDisplay(playback, library, parent);
}

QtSortHeader* QtViewFactory::createSortHeader(QWidget* parent) {
    return new QtSortHeader(parent);
}

QtSearchOverlay* QtViewFactory::createSearchOverlay(QWidget* parent) {
    return new QtSearchOverlay(parent);
}

QtTransportPanel* QtViewFactory::createTransport(IPlaybackControl& playback, QWidget* parent) {
    return new QtTransportPanel(playback, parent);
}

QtShuffleButton* QtViewFactory::createShuffleButton(IArrangementControl& arrangement, QWidget* parent) {
    return new QtShuffleButton(arrangement, parent);
}

QtRepeatButton* QtViewFactory::createRepeatButton(IArrangementControl& arrangement, QWidget* parent) {
    return new QtRepeatButton(arrangement, parent);
}

QtVolumePanel* QtViewFactory::createVolume(IPlaybackControl& playback, QWidget* parent) {
    return new QtVolumePanel(playback, parent);
}

QtToolbar* QtViewFactory::createToolbar(IPlaybackControl& playback, ILibraryControl& library, QWidget* parent) {
    return new QtToolbar(playback, library, parent);
}

QtNotification* QtViewFactory::createNotification(QWidget* parent) {
    return new QtNotification(parent);
}

QtDialog* QtViewFactory::createDialog(QWidget* parent) {
    return new QtDialog(parent);
}