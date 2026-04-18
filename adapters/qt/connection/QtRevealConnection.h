#ifndef QT_REVEAL_CONNECTION_H
#define QT_REVEAL_CONNECTION_H

#include "../widget/QtAdTimer.h"
#include "../../../view/IToolbarDisplay.h"
#include <QObject>

class QtRevealConnection final : public QObject {
private:
    IToolbarDisplay& toolbar_display_;

public:
    QtRevealConnection(QtAdTimer& timer, IToolbarDisplay& toolbar);

private slots:
    void relay() const;
};

#endif