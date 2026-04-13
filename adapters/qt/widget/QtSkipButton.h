#ifndef QT_SKIP_BUTTON_H
#define QT_SKIP_BUTTON_H

#include "../../../view/IPlaybackControl.h"
#include "../../../view/IToolbarDisplay.h"
#include "../../../view/IEnableable.h"
#include "IWidgetSetup.h"
#include <QWidget>
#include <QPushButton>

class QtSkipButton final : public QWidget, public IWidgetSetup, public IToolbarDisplay, public IEnableable {
    Q_OBJECT
private:
    QPushButton* button_;
    IPlaybackControl& playback_control_;

public:
    QtSkipButton(IPlaybackControl& playback, QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) override;
    void reveal(bool visible) override;
};

#endif //QT_SKIP_BUTTON_H
