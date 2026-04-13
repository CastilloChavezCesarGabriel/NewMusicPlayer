#ifndef QT_END_CONNECTION_H
#define QT_END_CONNECTION_H

#include "../widget/QtAudioEngine.h"
#include "../../../view/IAudioControl.h"
#include <QObject>

class QtEndConnection final : public QObject {
private:
    IAudioControl& playback_control_;

public:
    QtEndConnection(QtAudioEngine& audio, IAudioControl& playback);

private slots:
    void relay() const;
};

#endif