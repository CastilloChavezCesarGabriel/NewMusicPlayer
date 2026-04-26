#ifndef QT_SHUFFLE_BUTTON_H
#define QT_SHUFFLE_BUTTON_H

#include <QWidget>
#include <QPushButton>
#include "../../../view/IOrderControl.h"
#include "../../../view/IEnableable.h"
#include "IWidgetSetup.h"

class QtShuffleButton final : public QWidget, public IWidgetSetup, public IEnableable {
    Q_OBJECT
private:
    IOrderControl& order_;
    QPushButton* button_;

public:
    explicit QtShuffleButton(IOrderControl& order, QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) override;
};

#endif //QT_SHUFFLE_BUTTON_H