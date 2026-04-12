#ifndef PLAYLISTTEST_H
#define PLAYLISTTEST_H

#include <gtest/gtest.h>
#include "../../model/tracklist/Tracklist.h"
#include "../../model/tracklist/Cursor.h"
#include "../../model/event/TrackBus.h"
#include "../TestPlaylistVisitor.h"
#include "../MockPlaybackListener.h"
#include <memory>
#include <string>

class PlaylistTest : public ::testing::Test {
protected:
    std::string test_directory_;
    std::unique_ptr<Tracklist> tracklist_;
    std::unique_ptr<Cursor> cursor_;
    TestPlaylistVisitor visitor_;
    MockPlaybackListener listener_;
    TrackBus track_bus_;

    void SetUp() override;
    void TearDown() override;
    void populate(int count) const;
};

#endif
