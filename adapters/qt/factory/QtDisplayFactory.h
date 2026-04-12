#ifndef QT_DISPLAY_FACTORY_H
#define QT_DISPLAY_FACTORY_H

#include "../widget/QtPlaylistDisplay.h"
#include "../widget/QtSortHeader.h"
#include "../widget/QtSearchOverlay.h"
#include "../widget/QtToolbar.h"
#include "../../../view/IPlaybackControl.h"
#include "../../../view/ILibraryControl.h"
#include <QWidget>

class QtDisplayFactory {
public:
    static QtPlaylistDisplay* createDisplay(IPlaybackControl& playback, ILibraryControl& library, QWidget* parent = nullptr);
    static QtSortHeader* createSortHeader(QWidget* parent = nullptr);
    static QtSearchOverlay* createSearchOverlay(QWidget* parent = nullptr);
    static QtToolbar* createToolbar(IPlaybackControl& playback, ILibraryControl& library, QWidget* parent = nullptr);
};

#endif //QT_DISPLAY_FACTORY_H
