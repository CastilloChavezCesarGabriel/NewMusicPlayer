#ifndef QT_SORT_CONNECTION_H
#define QT_SORT_CONNECTION_H

#include "../widget/QtSortHeader.h"
#include "../../../view/IOrderControl.h"
#include <QObject>

class QtSortConnection final : public QObject {
private:
    IOrderControl& order_control_;

public:
    QtSortConnection(QtSortHeader& header, IOrderControl& order);

private slots:
    void relay() const;
};

#endif