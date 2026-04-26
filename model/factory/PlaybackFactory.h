#ifndef PLAYBACK_FACTORY_H
#define PLAYBACK_FACTORY_H

#include "../library/Dice.h"
#include "../playback/RandomAdPolicy.h"
#include "../playback/Advertisement.h"
#include "../playback/RepeatCoordinator.h"
#include "../playback/RepeatPolicy.h"
#include <memory>

class PlaybackFactory {
public:
    static Dice createDice();
    static std::unique_ptr<RandomAdPolicy> createAdPolicy(IDice& dice);
    static std::unique_ptr<Advertisement> createAdvertisement(IAdPolicy& adPolicy, IAdListener& adBus, ITrackListener& trackBus);
    static std::unique_ptr<RepeatCoordinator> createRepeatCoordinator(IRepeatListener& repeatBus, ITrackListener& trackBus);
    static std::unique_ptr<RepeatPolicy> createRepeatPolicy(TrackCursor& cursor, RepeatCoordinator& listener);
};

#endif //PLAYBACK_FACTORY_H