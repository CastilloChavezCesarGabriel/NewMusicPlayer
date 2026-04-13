#ifndef QT_VOLUME_PANEL_H
#define QT_VOLUME_PANEL_H

#include "../../../view/IAudioControl.h"
#include <QSlider>
#include <QLabel>

class QtVolumePanel final : public QWidget {
    Q_OBJECT
private:
    IAudioControl& playback_control_;
    QSlider* slider_;
    QLabel* label_;

public:
    explicit QtVolumePanel(IAudioControl& playback, QWidget* parent = nullptr);
    void adjust(int volume) const;
};

#endif //QT_VOLUME_PANEL_H