#include "QtArrangementFactory.h"

QtShuffleButton* QtArrangementFactory::createShuffleButton(IOrderControl& order, QWidget* parent) {
    return new QtShuffleButton(order, parent);
}

QtRepeatButton* QtArrangementFactory::createRepeatButton(IRepeatControl& repeat, QWidget* parent) {
    return new QtRepeatButton(repeat, parent);
}