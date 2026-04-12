#include "PlaybackFactory.h"

Dice PlaybackFactory::createDice() {
    return Dice();
}

std::unique_ptr<RandomAdPolicy> PlaybackFactory::createAdPolicy(IDice& dice) {
    return std::make_unique<RandomAdPolicy>(dice);
}

std::unique_ptr<Advertisement> PlaybackFactory::createAdvertisement(IAdPolicy& policy, IAdListener& adBus, ITrackListener& trackBus) {
    return std::make_unique<Advertisement>(policy, adBus, trackBus);
}

std::unique_ptr<RepeatListener> PlaybackFactory::createRepeatListener(IRepeatListener& repeatBus, ITrackListener& trackBus) {
    return std::make_unique<RepeatListener>(repeatBus, trackBus);
}

std::unique_ptr<RepeatMode> PlaybackFactory::createRepeatMode(Cursor& cursor, RepeatListener& listener) {
    return std::make_unique<RepeatMode>(cursor, listener);
}