#include "PlaybackFactory.h"
#include "../playback/NoRepeatStrategy.h"
#include "../playback/RepeatOneStrategy.h"
#include "../playback/RepeatAllStrategy.h"

Dice PlaybackFactory::createDice() {
    return Dice();
}

std::unique_ptr<RandomAdPolicy> PlaybackFactory::createAdPolicy(IDice& dice) {
    return std::make_unique<RandomAdPolicy>(dice);
}

std::unique_ptr<AdScheduler> PlaybackFactory::createAdScheduler(IAdPolicy& adPolicy, IAdListener& adBus, ITrackListener& trackBus) {
    return std::make_unique<AdScheduler>(adPolicy, adBus, trackBus);
}

std::unique_ptr<RepeatBroadcaster> PlaybackFactory::createRepeatBroadcaster(IRepeatListener& repeatBus, ITrackListener& trackBus) {
    return std::make_unique<RepeatBroadcaster>(repeatBus, trackBus);
}

std::unique_ptr<RepeatPolicy> PlaybackFactory::createRepeatPolicy(TrackCursor& cursor, RepeatBroadcaster& listener) {
    auto mode = std::make_unique<RepeatPolicy>(cursor, listener);
    mode->add(std::make_unique<NoRepeatStrategy>());
    mode->add(std::make_unique<RepeatOneStrategy>());
    mode->add(std::make_unique<RepeatAllStrategy>());
    return mode;
}