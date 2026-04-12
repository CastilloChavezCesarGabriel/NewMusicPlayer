#include "QtPlaybackFactory.h"

QtAudioEngine* QtPlaybackFactory::createAudio(QWidget* parent) {
    return new QtAudioEngine(parent);
}

QtTransportPanel* QtPlaybackFactory::createTransport(IPlaybackControl& playback, QWidget* parent) {
    return new QtTransportPanel(playback, parent);
}

QtVolumePanel* QtPlaybackFactory::createVolume(IPlaybackControl& playback, QWidget* parent) {
    return new QtVolumePanel(playback, parent);
}
