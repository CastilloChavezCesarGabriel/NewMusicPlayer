#ifndef QT_END_CONNECTION_H
#define QT_END_CONNECTION_H

#include "../widget/QtAudioEngine.h"
#include "../../../view/IPlaybackControl.h"
#include <QObject>

class QtEndConnection final : public QObject {
private:
    IPlaybackControl& playback_control_;

public:
    QtEndConnection(QtAudioEngine& audio, IPlaybackControl& playback);

private slots:
    void relay() const;
};

#endif