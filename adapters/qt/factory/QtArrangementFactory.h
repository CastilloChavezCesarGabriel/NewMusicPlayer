#ifndef QT_ARRANGEMENT_FACTORY_H
#define QT_ARRANGEMENT_FACTORY_H

#include "../widget/QtShuffleButton.h"
#include "../widget/QtRepeatButton.h"
#include "../../../view/IOrderControl.h"
#include "../../../view/IRepeatControl.h"
#include <QWidget>

class QtArrangementFactory {
public:
    static QtShuffleButton* createShuffleButton(IOrderControl& order, QWidget* parent = nullptr);
    static QtRepeatButton* createRepeatButton(IRepeatControl& repeat, QWidget* parent = nullptr);
};

#endif //QT_ARRANGEMENT_FACTORY_H