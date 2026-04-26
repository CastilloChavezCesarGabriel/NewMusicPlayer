#ifndef PRESENTER_FACTORY_H
#define PRESENTER_FACTORY_H

#include "../TrackPresenter.h"
#include "../LibraryPresenter.h"
#include "../ArrangementPresenter.h"
#include "../AdPresenter.h"
#include "../RepeatPresenter.h"
#include <memory>

class PresenterFactory {
public:
    static std::unique_ptr<TrackPresenter> createTrackPresenter(IAudioPlayer& audio, IPlaylistPanel& display, IEnableable& enable);
    static std::unique_ptr<LibraryPresenter> createLibraryPresenter(TrackCatalog& catalog, IPlaylistPanel& display, INotification& notification);
    static std::unique_ptr<ArrangementPresenter> createArrangementPresenter(PlaybackModeController& arrangement);
    static std::unique_ptr<AdPresenter> createAdPresenter(IEnableable& enable, ITimingPanel& timing, IToolbarDisplay& toolbar);
    static std::unique_ptr<RepeatPresenter> createRepeatPresenter(IRepeatDisplay& display);
};

#endif //PRESENTER_FACTORY_H
