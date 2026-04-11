#ifndef MODEL_TEST_FIXTURE_H
#define MODEL_TEST_FIXTURE_H

#include <gtest/gtest.h>
#include "../model/Dice.h"
#include "../model/RandomAdPolicy.h"
#include "../model/TrackBus.h"
#include "../model/LibraryBus.h"
#include "../model/AdBus.h"
#include "../model/RepeatBus.h"
#include "../model/RepeatListener.h"
#include "../model/MusicDirectory.h"
#include "../model/Tracklist.h"
#include "../model/Cursor.h"
#include "../model/ShuffleArrangement.h"
#include "../model/Advertisement.h"
#include "../model/RepeatMode.h"
#include "../model/service/Playback.h"
#include "../model/service/Library.h"
#include "../model/service/Setlist.h"
#include "../model/service/Catalog.h"
#include "../model/service/RepeatSwitch.h"
#include "MockPlaybackListener.h"
#include "TestPlaylistVisitor.h"
#include <memory>
#include <string>

class ModelTestFixture : public ::testing::Test {
protected:
    std::string base_directory_;
    std::string music_directory_;
    std::string ads_directory_;
    MockPlaybackListener listener_;
    Dice dice_;
    std::unique_ptr<RandomAdPolicy> ad_policy_;

    TrackBus track_bus_;
    LibraryBus library_bus_;
    AdBus ad_bus_;
    RepeatBus repeat_bus_;
    std::unique_ptr<RepeatListener> repeat_listener_;
    std::unique_ptr<MusicDirectory> directory_;
    std::unique_ptr<Tracklist> tracklist_;
    std::unique_ptr<Cursor> cursor_;
    std::unique_ptr<Advertisement> advertisement_;
    std::unique_ptr<RepeatMode> repeat_mode_;
    std::unique_ptr<Playback> playback_;
    std::unique_ptr<Library> library_;
    std::unique_ptr<Setlist> setlist_;
    std::unique_ptr<Catalog> catalog_;
    std::unique_ptr<RepeatSwitch> repeat_switch_;

    void SetUp() override;
    void TearDown() override;
    void createSong(const std::string& name) const;
    void createAd(const std::string& name) const;
    void build();
    virtual std::string identify() const = 0;
};

#endif //MODEL_TEST_FIXTURE_H
