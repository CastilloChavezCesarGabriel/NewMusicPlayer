#ifndef QT_TOGGLE_CONNECTION_H
#define QT_TOGGLE_CONNECTION_H

#include "../widget/QtAudioEngine.h"
#include "../../../view/IPlaybackDisplay.h"
#include <QObject>

class QtToggleConnection final : public QObject {
private:
    IPlaybackDisplay& playback_display_;

public:
    QtToggleConnection(QtAudioEngine& audio, IPlaybackDisplay& display);

private slots:
    void relay(bool playing) const;
};

#endif