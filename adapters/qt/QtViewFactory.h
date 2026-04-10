#ifndef QT_VIEW_FACTORY_H
#define QT_VIEW_FACTORY_H

#include "QtTransportPanel.h"
#include "QtArrangementPanel.h"
#include "QtVolumePanel.h"
#include "QtToolbar.h"
#include "QtNotification.h"
#include "QtDialog.h"
#include <QWidget>
#include "../../view/IPlaybackControl.h"
#include "../../view/IArrangementControl.h"

class QtViewFactory {
public:
    static QtTransportPanel* createTransport(IPlaybackControl& playback, QWidget* parent);
    static QtArrangementPanel* createArrangement(IArrangementControl& arrangement, QWidget* parent);
    static QtVolumePanel* createVolume(IPlaybackControl& playback, QWidget* parent);
    static QtToolbar* createToolbar(QWidget* parent);
    static QtNotification* createNotification(QWidget* parent);
    static QtDialog* createDialog(QWidget* parent);
};

#endif //QT_VIEW_FACTORY_H