#ifndef QT_PLAYBACK_FACTORY_H
#define QT_PLAYBACK_FACTORY_H

#include "../widget/QtAudioEngine.h"
#include "../widget/QtTransportPanel.h"
#include "../widget/QtVolumePanel.h"
#include "../widget/QtSkipButton.h"
#include "../../../view/IPlaybackControl.h"
#include <QWidget>

class QtPlaybackFactory {
public:
    static QtAudioEngine* createAudio(QWidget* parent = nullptr);
    static QtTransportPanel* createTransport(IPlaybackControl& playback, QWidget* parent = nullptr);
    static QtVolumePanel* createVolume(IPlaybackControl& playback, QWidget* parent = nullptr);
    static QtSkipButton* createSkipButton(IPlaybackControl& playback, QWidget* parent = nullptr);
};

#endif //QT_PLAYBACK_FACTORY_H
