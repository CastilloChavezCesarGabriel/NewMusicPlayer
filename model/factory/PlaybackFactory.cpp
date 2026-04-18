#include "PlaybackFactory.h"
#include "../playback/NoRepeatMode.h"
#include "../playback/RepeatOneMode.h"
#include "../playback/RepeatAllMode.h"

Dice PlaybackFactory::createDice() {
    return Dice();
}

std::unique_ptr<RandomAdPolicy> PlaybackFactory::createAdPolicy(IDice& dice) {
    return std::make_unique<RandomAdPolicy>(dice);
}

std::unique_ptr<Advertisement> PlaybackFactory::createAdvertisement(IAdPolicy& adPolicy, IAdListener& adBus, ITrackListener& trackBus) {
    return std::make_unique<Advertisement>(adPolicy, adBus, trackBus);
}

std::unique_ptr<RepeatCoordinator> PlaybackFactory::createRepeatCoordinator(IRepeatListener& repeatBus, ITrackListener& trackBus) {
    return std::make_unique<RepeatCoordinator>(repeatBus, trackBus);
}

std::unique_ptr<RepeatMode> PlaybackFactory::createRepeatMode(TrackCursor& cursor, RepeatCoordinator& listener) {
    auto mode = std::make_unique<RepeatMode>(cursor, listener);
    mode->add(std::make_unique<NoRepeatMode>());
    mode->add(std::make_unique<RepeatOneMode>());
    mode->add(std::make_unique<RepeatAllMode>());
    return mode;
}