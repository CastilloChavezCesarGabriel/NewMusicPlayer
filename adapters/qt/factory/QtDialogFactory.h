#ifndef QT_DIALOG_FACTORY_H
#define QT_DIALOG_FACTORY_H

#include "../widget/QtNotification.h"
#include "../widget/QtDialog.h"
#include <QWidget>

class QtDialogFactory {
public:
    static QtNotification* createNotification(QWidget* parent = nullptr);
    static QtDialog* createDialog(QWidget* parent = nullptr);
};

#endif //QT_DIALOG_FACTORY_H
