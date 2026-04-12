#include "QtArrangementFactory.h"

QtShuffleButton* QtArrangementFactory::createShuffleButton(IArrangementControl& arrangement, QWidget* parent) {
    return new QtShuffleButton(arrangement, parent);
}

QtRepeatButton* QtArrangementFactory::createRepeatButton(IArrangementControl& arrangement, QWidget* parent) {
    return new QtRepeatButton(arrangement, parent);
}
