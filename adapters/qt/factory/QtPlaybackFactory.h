#ifndef QT_PLAYBACK_FACTORY_H
#define QT_PLAYBACK_FACTORY_H

#include "../widget/QtAudioEngine.h"
#include "../widget/QtAdTimer.h"
#include "../widget/QtTransportPanel.h"
#include "../widget/QtVolumePanel.h"
#include "../widget/QtSkipButton.h"
#include "../../../view/IPlaybackControl.h"
#include "../../../view/IAudioControl.h"
#include <QWidget>
#include <QObject>

class QtPlaybackFactory {
public:
    static QtAudioEngine* createAudio(QWidget* parent = nullptr);
    static QtAdTimer* createAdTimer(QObject* parent = nullptr);
    static QtTransportPanel* createTransport(IPlaybackControl& playback, QWidget* parent = nullptr);
    static QtVolumePanel* createVolume(IAudioControl& audio, QWidget* parent = nullptr);
    static QtSkipButton* createSkipButton(IAudioControl& audio, QWidget* parent = nullptr);
};

#endif //QT_PLAYBACK_FACTORY_H
