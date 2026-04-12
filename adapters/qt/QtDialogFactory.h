#ifndef QT_DIALOG_FACTORY_H
#define QT_DIALOG_FACTORY_H

#include "QtNotification.h"
#include "QtDialog.h"
#include <QWidget>

class QtDialogFactory {
public:
    static QtNotification* createNotification(QWidget* parent = nullptr);
    static QtDialog* createDialog(QWidget* parent = nullptr);
};

#endif //QT_DIALOG_FACTORY_H
