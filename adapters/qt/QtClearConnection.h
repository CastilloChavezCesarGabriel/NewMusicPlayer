#ifndef QT_CLEAR_CONNECTION_H
#define QT_CLEAR_CONNECTION_H

#include "QtSearchOverlay.h"
#include "QtSearchField.h"
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