#ifndef QT_SKIP_BUTTON_H
#define QT_SKIP_BUTTON_H

#include "../../../view/IAudioControl.h"
#include "../../../view/IToolbarDisplay.h"
#include "../../../view/IEnableable.h"
#include "IWidgetSetup.h"
#include <QWidget>
#include <QPushButton>

class QtSkipButton final : public QWidget, public IWidgetSetup, public IToolbarDisplay, public IEnableable {
    Q_OBJECT
private:
    QPushButton* button_;
    IAudioControl& playback_control_;

public:
    QtSkipButton(IAudioControl& playback, QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) override;
    void reveal(bool visible) override;
};

#endif //QT_SKIP_BUTTON_H
