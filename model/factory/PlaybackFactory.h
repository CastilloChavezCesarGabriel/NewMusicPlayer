#ifndef PLAYBACK_FACTORY_H
#define PLAYBACK_FACTORY_H

#include "../library/Dice.h"
#include "../playback/RandomAdPolicy.h"
#include "../playback/AdScheduler.h"
#include "../playback/RepeatBroadcaster.h"
#include "../playback/RepeatPolicy.h"
#include <memory>

class PlaybackFactory {
public:
    static Dice createDice();
    static std::unique_ptr<RandomAdPolicy> createAdPolicy(IDice& dice);
    static std::unique_ptr<AdScheduler> createAdScheduler(IAdPolicy& adPolicy, IAdListener& adBus, ITrackListener& trackBus);
    static std::unique_ptr<RepeatBroadcaster> createRepeatBroadcaster(IRepeatListener& repeatBus, ITrackListener& trackBus);
    static std::unique_ptr<RepeatPolicy> createRepeatPolicy(TrackCursor& cursor, RepeatBroadcaster& listener);
};

#endif //PLAYBACK_FACTORY_H