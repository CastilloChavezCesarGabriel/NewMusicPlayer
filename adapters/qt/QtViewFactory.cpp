#include "QtViewFactory.h"

QtPlaybackPanel* QtViewFactory::createPlayback(IPlaybackControl& playback, IArrangementControl& arrangement, QWidget* parent) {
    return new QtPlaybackPanel(playback, arrangement, parent);
}

QtVolumePanel* QtViewFactory::createVolume(IPlaybackControl& playback, QWidget* parent) {
    return new QtVolumePanel(playback, parent);
}

QtToolbar* QtViewFactory::createToolbar(QWidget* parent) {
    return new QtToolbar(parent);
}

QtNotification* QtViewFactory::createNotification(QWidget* parent) {
    return new QtNotification(parent);
}

QtDialog* QtViewFactory::createDialog(QWidget* parent) {
    return new QtDialog(parent);
}
