#ifndef PLAYBACK_FACTORY_H
#define PLAYBACK_FACTORY_H

#include "../model/Dice.h"
#include "../model/RandomAdPolicy.h"
#include "../model/Advertisement.h"
#include "../model/RepeatListener.h"
#include "../model/RepeatMode.h"
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
