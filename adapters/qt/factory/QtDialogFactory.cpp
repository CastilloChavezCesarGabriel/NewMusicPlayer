#include "QtDialogFactory.h"

QtNotification* QtDialogFactory::createNotification(QWidget* parent) {
    return new QtNotification(parent);
}

QtDialog* QtDialogFactory::createDialog(QWidget* parent) {
    return new QtDialog(parent);
}