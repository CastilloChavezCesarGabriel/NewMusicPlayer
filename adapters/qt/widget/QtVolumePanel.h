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

    void slide(int volume) const;
    void adjust(int volume) const;

public:
    explicit QtVolumePanel(IAudioControl& playback, QWidget* parent = nullptr);
};

#endif //QT_VOLUME_PANEL_H