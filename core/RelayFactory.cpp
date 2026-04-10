#include "RelayFactory.h"

std::unique_ptr<TrackRelay> RelayFactory::createTrackRelay(IAudioPlayer& audio, IPlaylistPanel& display, IEnableable& enable) {
    return std::make_unique<TrackRelay>(audio, display, enable);
}

std::unique_ptr<LibraryRelay> RelayFactory::createLibraryRelay(Catalog& catalog, IPlaylistPanel& display, INotification& notification) {
    return std::make_unique<LibraryRelay>(catalog, display, notification);
}

std::unique_ptr<AdRelay> RelayFactory::createAdRelay(IEnableable& enable, ITimingPanel& timing, IToolbarDisplay& toolbar) {
    return std::make_unique<AdRelay>(enable, timing, toolbar);
}

std::unique_ptr<RepeatRelay> RelayFactory::createRepeatRelay(IRepeatDisplay& display) {
    return std::make_unique<RepeatRelay>(display);
}
