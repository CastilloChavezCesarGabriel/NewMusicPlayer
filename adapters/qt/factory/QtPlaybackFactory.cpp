#include "QtPlaybackFactory.h"

QtAudioEngine* QtPlaybackFactory::createAudio(QWidget* parent) {
    return new QtAudioEngine(parent);
}

QtAdTimer* QtPlaybackFactory::createAdTimer(QObject* parent) {
    return new QtAdTimer(parent);
}

QtTransportPanel* QtPlaybackFactory::createTransport(IPlaybackControl& playback, QWidget* parent) {
    return new QtTransportPanel(playback, parent);
}

QtVolumePanel* QtPlaybackFactory::createVolume(IAudioControl& audio, QWidget* parent) {
    return new QtVolumePanel(audio, parent);
}

QtSkipButton* QtPlaybackFactory::createSkipButton(IAudioControl& audio, QWidget* parent) {
    return new QtSkipButton(audio, parent);
}
