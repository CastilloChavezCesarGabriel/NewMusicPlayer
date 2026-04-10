#ifndef ADVERTISEMENTTEST_H
#define ADVERTISEMENTTEST_H

#include "../DirectoryTestFixture.h"
#include "../MockPlaybackListener.h"
#include "../../model/Dice.h"
#include "../../model/RandomAdPolicy.h"
#include "../../model/AdBus.h"
#include "../../model/TrackBus.h"

class AdvertisementTest : public DirectoryTestFixture {
protected:
    MockPlaybackListener listener_;
    Dice dice_;
    RandomAdPolicy ad_policy_{dice_};
    AdBus ad_bus_;
    TrackBus track_bus_;

    void SetUp() override;
    std::string identify() const override;
};

#endif
