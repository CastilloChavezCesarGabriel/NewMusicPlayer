#ifndef QT_VIEW_FACTORY_H
#define QT_VIEW_FACTORY_H

#include "QtAudioEngine.h"
#include "QtPlaylistDisplay.h"
#include "QtSortHeader.h"
#include "QtSearchOverlay.h"
#include "QtTransportPanel.h"
#include "QtArrangementPanel.h"
#include "QtVolumePanel.h"
#include "QtToolbar.h"
#include "QtNotification.h"
#include "QtDialog.h"
#include <QWidget>
#include "../../view/IPlaybackControl.h"
#include "../../view/ILibraryControl.h"

class QtViewFactory {
public:
    static QtAudioEngine* createAudio(QWidget* parent = nullptr);
    static QtPlaylistDisplay* createDisplay(IPlaybackControl& playback, ILibraryControl& library, QWidget* parent = nullptr);
    static QtSortHeader* createSortHeader(QWidget* parent = nullptr);
    static QtSearchOverlay* createSearchOverlay(QWidget* parent = nullptr);
    static QtTransportPanel* createTransport(IPlaybackControl& playback, QWidget* parent = nullptr);
    static QtArrangementPanel* createArrangement(IArrangementControl& arrangement, QWidget* parent = nullptr);
    static QtVolumePanel* createVolume(IPlaybackControl& playback, QWidget* parent = nullptr);
    static QtToolbar* createToolbar(IPlaybackControl& playback, ILibraryControl& library, QWidget* parent = nullptr);
    static QtNotification* createNotification(QWidget* parent = nullptr);
    static QtDialog* createDialog(QWidget* parent = nullptr);
};

#endif //QT_VIEW_FACTORY_H