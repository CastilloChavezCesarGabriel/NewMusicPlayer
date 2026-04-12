#ifndef QT_ARRANGEMENT_FACTORY_H
#define QT_ARRANGEMENT_FACTORY_H

#include "QtShuffleButton.h"
#include "QtRepeatButton.h"
#include "../../view/IArrangementControl.h"
#include <QWidget>

class QtArrangementFactory {
public:
    static QtShuffleButton* createShuffleButton(IArrangementControl& arrangement, QWidget* parent = nullptr);
    static QtRepeatButton* createRepeatButton(IArrangementControl& arrangement, QWidget* parent = nullptr);
};

#endif //QT_ARRANGEMENT_FACTORY_H
