#include "PresenterFactory.h"

std::unique_ptr<TrackPresenter> PresenterFactory::createTrackPresenter(IAudioPlayer& audio, IPlaylistPanel& display, IEnableable& enable) {
    return std::make_unique<TrackPresenter>(audio, display, enable);
}

std::unique_ptr<LibraryPresenter> PresenterFactory::createLibraryPresenter(TrackCatalog& catalog, IPlaylistPanel& display, INotification& notification) {
    return std::make_unique<LibraryPresenter>(catalog, display, notification);
}

std::unique_ptr<ArrangementPresenter> PresenterFactory::createArrangementPresenter(PlaybackModeController& arrangement) {
    return std::make_unique<ArrangementPresenter>(arrangement);
}

std::unique_ptr<AdPresenter> PresenterFactory::createAdPresenter(IEnableable& enable, ITimingPanel& timing, IToolbarDisplay& toolbar) {
    return std::make_unique<AdPresenter>(enable, timing, toolbar);
}

std::unique_ptr<RepeatPresenter> PresenterFactory::createRepeatPresenter(IRepeatDisplay& display) {
    return std::make_unique<RepeatPresenter>(display);
}