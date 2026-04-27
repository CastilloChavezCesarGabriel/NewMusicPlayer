#ifndef MODEL_TEST_FIXTURE_H
#define MODEL_TEST_FIXTURE_H

#include <gtest/gtest.h>
#include "../model/library/Dice.h"
#include "../model/playback/RandomAdPolicy.h"
#include "../model/event/TrackBus.h"
#include "../model/event/LibraryBus.h"
#include "../model/event/AdBus.h"
#include "../model/event/RepeatBus.h"
#include "../model/playback/RepeatBroadcaster.h"
#include "../model/library/MusicDirectory.h"
#include "../model/tracklist/Tracklist.h"
#include "../model/tracklist/TrackCursor.h"
#include "../model/playback/AdScheduler.h"
#include "../model/playback/RepeatPolicy.h"
#include "../model/service/PlaybackTransport.h"
#include "../model/service/LibraryEditor.h"
#include "../model/service/Setlist.h"
#include "../model/service/TrackCatalog.h"
#include "TrackListenerSpy.h"
#include "LibraryListenerSpy.h"
#include "AdListenerSpy.h"
#include <memory>
#include <string>

class ModelTestFixture : public ::testing::Test {
protected:
    Dice dice_;
    TrackBus track_bus_;
    LibraryBus library_bus_;
    AdBus ad_bus_;
    RepeatBus repeat_bus_;
    std::string base_directory_;
    std::string music_directory_;
    std::string ads_directory_;
    TrackListenerSpy track_spy_;
    LibraryListenerSpy library_spy_;
    AdListenerSpy ad_spy_;
    std::unique_ptr<RandomAdPolicy> ad_policy_;
    std::unique_ptr<RepeatBroadcaster> repeat_listener_;
    std::unique_ptr<MusicDirectory> directory_;
    std::unique_ptr<Tracklist> tracklist_;
    std::unique_ptr<TrackCursor> cursor_;
    std::unique_ptr<AdScheduler> ad_scheduler_;
    std::unique_ptr<RepeatPolicy> repeat_policy_;
    std::unique_ptr<PlaybackTransport> playback_;
    std::unique_ptr<LibraryEditor> library_;
    std::unique_ptr<Setlist> setlist_;
    std::unique_ptr<TrackCatalog> catalog_;

    void SetUp() override;
    void TearDown() override;
    std::string prepare(const std::string& name) const;
    void createSong(const std::string& name) const;
    void createAd(const std::string& name) const;
    void build();
    virtual std::string identify() const = 0;
};

#endif //MODEL_TEST_FIXTURE_H