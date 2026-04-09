#ifndef MODEL_TEST_FIXTURE_H
#define MODEL_TEST_FIXTURE_H

#include <gtest/gtest.h>
#include "../model/Dice.h"
#include "../model/PlaybackNotifier.h"
#include "../model/MusicLibrary.h"
#include "../model/Playlist.h"
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

    PlaybackNotifier notifier_;
    std::unique_ptr<MusicLibrary> music_library_;
    std::unique_ptr<Playlist> playlist_;
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
