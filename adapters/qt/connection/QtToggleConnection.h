#ifndef QT_TOGGLE_CONNECTION_H
#define QT_TOGGLE_CONNECTION_H

#include "../widget/QtAudioEngine.h"
#include "../widget/QtTransportPanel.h"
#include <QObject>

class QtToggleConnection final : public QObject {
private:
    QtTransportPanel& transport_;

public:
    QtToggleConnection(QtAudioEngine& audio, QtTransportPanel& transport);

private slots:
    void relay(bool playing) const;
};

#endif