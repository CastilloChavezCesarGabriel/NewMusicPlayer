#ifndef RELAY_FACTORY_H
#define RELAY_FACTORY_H

#include "../controller/TrackRelay.h"
#include "../controller/LibraryRelay.h"
#include "../controller/AdRelay.h"
#include "../controller/RepeatRelay.h"
#include <memory>

class RelayFactory {
public:
    static std::unique_ptr<TrackRelay> createTrackRelay(IAudioPlayer& audio, IPlaylistPanel& display, IEnableable& enable);
    static std::unique_ptr<LibraryRelay> createLibraryRelay(Catalog& catalog, IPlaylistPanel& display, INotification& notification);
    static std::unique_ptr<AdRelay> createAdRelay(IEnableable& enable, ITimingPanel& timing, IToolbarDisplay& toolbar);
    static std::unique_ptr<RepeatRelay> createRepeatRelay(IRepeatDisplay& display);
};

#endif //RELAY_FACTORY_H