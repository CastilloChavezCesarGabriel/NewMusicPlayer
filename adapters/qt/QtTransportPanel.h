#ifndef QT_TRANSPORT_PANEL_H
#define QT_TRANSPORT_PANEL_H

#include <QWidget>
#include <QPushButton>
#include "../../view/IPlaybackControl.h"
#include "../../view/IPlaybackDisplay.h"
#include "../../view/IEnableable.h"
#include "IWidgetSetup.h"

class QtTransportPanel final : public QWidget, public IWidgetSetup, public IPlaybackDisplay, public IEnableable {
    Q_OBJECT
private:
    IPlaybackControl& playback_;
    QPushButton* toggle_;
    QPushButton* next_;
    QPushButton* previous_;

public:
    explicit QtTransportPanel(IPlaybackControl& playback, QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) override;
    void toggle(bool playing) override;
};

#endif
