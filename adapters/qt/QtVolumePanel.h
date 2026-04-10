#ifndef QT_VOLUME_PANEL_H
#define QT_VOLUME_PANEL_H

#include "../../view/IPlaybackControl.h"
#include <QSlider>
#include <QLabel>

class QtVolumePanel final : public QWidget {
    Q_OBJECT
private:
    IPlaybackControl& playback_control_;
    QSlider* slider_;
    QLabel* label_;

public:
    explicit QtVolumePanel(IPlaybackControl& playback, QWidget* parent = nullptr);
    void adjust(int volume) const;
};

#endif //QT_VOLUME_PANEL_H