#ifndef QT_REMOVE_CONNECTION_H
#define QT_REMOVE_CONNECTION_H

#include "../widget/QtToolbar.h"
#include "../widget/QtPlaylistDisplay.h"
#include <QObject>

class QtRemoveConnection final : public QObject {
public:
    QtRemoveConnection(QtToolbar& toolbar, QtPlaylistDisplay& display);
};

#endif