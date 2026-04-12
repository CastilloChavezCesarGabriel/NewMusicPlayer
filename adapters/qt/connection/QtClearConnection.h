#ifndef QT_CLEAR_CONNECTION_H
#define QT_CLEAR_CONNECTION_H

#include "../widget/QtSearchOverlay.h"
#include "../widget/QtSearchField.h"
#include <QObject>

class QtClearConnection final : public QObject {
private:
    QtSearchField& search_field_;

public:
    QtClearConnection(QtSearchOverlay& overlay, QtSearchField& field);

private slots:
    void relay() const;
};

#endif