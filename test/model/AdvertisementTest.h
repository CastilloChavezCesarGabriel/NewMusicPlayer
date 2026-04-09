#ifndef ADVERTISEMENTTEST_H
#define ADVERTISEMENTTEST_H

#include "../DirectoryTestFixture.h"
#include "../MockPlaybackListener.h"
#include "../../model/Dice.h"
#include "../../model/PlaybackNotifier.h"

class AdvertisementTest : public DirectoryTestFixture {
protected:
    MockPlaybackListener listener_;
    Dice dice_;
    PlaybackNotifier notifier_;

    void SetUp() override;
    std::string identify() const override;
};

#endif
