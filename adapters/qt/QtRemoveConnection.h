#ifndef QT_REMOVE_CONNECTION_H
#define QT_REMOVE_CONNECTION_H

#include "QtToolbar.h"
#include "QtPlaylistDisplay.h"
#include <QObject>

class QtRemoveConnection final : public QObject {
public:
    QtRemoveConnection(QtToolbar& toolbar, QtPlaylistDisplay& display);
};

#endif