#ifndef ADVERTISEMENTTEST_H
#define ADVERTISEMENTTEST_H

#include "../DirectoryTestFixture.h"
#include "../TrackListenerSpy.h"
#include "../../model/library/Dice.h"
#include "../../model/playback/RandomAdPolicy.h"
#include "../../model/event/AdBus.h"
#include "../../model/event/TrackBus.h"
#include "../../model/playback/AdScheduler.h"

class AdSchedulerTest : public DirectoryTestFixture {
protected:
    TrackListenerSpy track_spy_;
    Dice dice_;
    RandomAdPolicy ad_policy_{dice_};
    AdBus ad_bus_;
    TrackBus track_bus_;

    void SetUp() override;
    std::string identify() const override;
    static bool interruptsAtLeastOnce(AdScheduler& ad);
};

#endif