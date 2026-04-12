#ifndef PLAYBACK_FACTORY_H
#define PLAYBACK_FACTORY_H

#include "../library/Dice.h"
#include "../playback/RandomAdPolicy.h"
#include "../playback/Advertisement.h"
#include "../playback/RepeatListener.h"
#include "../playback/RepeatMode.h"
#include <memory>

class PlaybackFactory {
public:
    static Dice createDice();
    static std::unique_ptr<RandomAdPolicy> createAdPolicy(IDice& dice);
    static std::unique_ptr<Advertisement> createAdvertisement(IAdPolicy& policy, IAdListener& adBus, ITrackListener& trackBus);
    static std::unique_ptr<RepeatListener> createRepeatListener(IRepeatListener& repeatBus, ITrackListener& trackBus);
    static std::unique_ptr<RepeatMode> createRepeatMode(Cursor& cursor, RepeatListener& listener);
};

#endif //PLAYBACK_FACTORY_H