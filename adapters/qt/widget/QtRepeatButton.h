#ifndef QT_REPEAT_BUTTON_H
#define QT_REPEAT_BUTTON_H

#include <QWidget>
#include <QPushButton>
#include "../../../view/IArrangementControl.h"
#include "../../../view/IRepeatDisplay.h"
#include "IWidgetSetup.h"

class QtRepeatButton final : public QWidget, public IWidgetSetup, public IRepeatDisplay {
    Q_OBJECT
private:
    IArrangementControl& arrangement_;
    QPushButton* button_;

public:
    explicit QtRepeatButton(IArrangementControl& arrangement, QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) override;
    void repeat(int mode) override;
};

#endif //QT_REPEAT_BUTTON_H
