#ifndef MODEL_TEST_FIXTURE_H
#define MODEL_TEST_FIXTURE_H

#include <gtest/gtest.h>
#include "../model/library/Dice.h"
#include "../model/playback/RandomAdPolicy.h"
#include "../model/event/TrackBus.h"
#include "../model/event/LibraryBus.h"
#include "../model/event/AdBus.h"
#include "../model/event/RepeatBus.h"
#include "../model/playback/RepeatCoordinator.h"
#include "../model/library/MusicDirectory.h"
#include "../model/tracklist/Tracklist.h"
#include "../model/tracklist/TrackCursor.h"
#include "../model/tracklist/ShuffleArrangement.h"
#include "../model/playback/Advertisement.h"
#include "../model/playback/RepeatMode.h"
#include "../model/service/PlaybackService.h"
#include "../model/service/LibraryService.h"
#include "../model/service/Setlist.h"
#include "../model/service/TrackCatalog.h"
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
    std::unique_ptr<RepeatCoordinator> repeat_listener_;
    std::unique_ptr<MusicDirectory> directory_;
    std::unique_ptr<Tracklist> tracklist_;
    std::unique_ptr<TrackCursor> cursor_;
    std::unique_ptr<Advertisement> advertisement_;
    std::unique_ptr<RepeatMode> repeat_mode_;
    std::unique_ptr<PlaybackService> playback_;
    std::unique_ptr<LibraryService> library_;
    std::unique_ptr<Setlist> setlist_;
    std::unique_ptr<TrackCatalog> catalog_;

    void SetUp() override;
    void TearDown() override;
    void createSong(const std::string& name) const;
    void createAd(const std::string& name) const;
    void build();
    virtual std::string identify() const = 0;
};

#endif //MODEL_TEST_FIXTURE_H
