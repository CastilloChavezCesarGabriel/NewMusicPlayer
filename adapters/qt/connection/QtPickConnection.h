#ifndef QT_PICK_CONNECTION_H
#define QT_PICK_CONNECTION_H

#include "../widget/QtSearchOverlay.h"
#include "../../../view/IDisplayControl.h"
#include <QObject>

class QtPickConnection final : public QObject {
private:
    IDisplayControl& display_control_;

public:
    QtPickConnection(QtSearchOverlay& overlay, IDisplayControl& display);

private slots:
    void relay(const std::string& name) const;
};

#endif