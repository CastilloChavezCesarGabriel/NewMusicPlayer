#include "QtViewFactory.h"

QtTransportPanel* QtViewFactory::createTransport(IPlaybackControl& playback, QWidget* parent) {
    return new QtTransportPanel(playback, parent);
}

QtArrangementPanel* QtViewFactory::createArrangement(IArrangementControl& arrangement, QWidget* parent) {
    return new QtArrangementPanel(arrangement, parent);
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
