#ifndef QT_SORT_CONNECTION_H
#define QT_SORT_CONNECTION_H

#include "../widget/QtSortHeader.h"
#include "../../../view/IArrangementControl.h"
#include <QObject>

class QtSortConnection final : public QObject {
private:
    IArrangementControl& arrangement_control_;

public:
    QtSortConnection(QtSortHeader& header, IArrangementControl& arrangement);

private slots:
    void relay() const;
};

#endif