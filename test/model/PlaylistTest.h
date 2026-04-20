#ifndef PLAYLISTTEST_H
#define PLAYLISTTEST_H

#include "../DirectoryTestFixture.h"
#include "../../model/tracklist/Tracklist.h"
#include "../../model/tracklist/TrackCursor.h"
#include "../../model/event/TrackBus.h"
#include "../TestPlaylistVisitor.h"
#include "../MockPlaybackListener.h"
#include <memory>
#include <string>

class PlaylistTest : public DirectoryTestFixture {
protected:
    std::unique_ptr<Tracklist> tracklist_;
    std::unique_ptr<TrackCursor> cursor_;
    TestPlaylistVisitor visitor_;
    MockPlaybackListener listener_;
    TrackBus track_bus_;

    std::string identify() const override;
    void SetUp() override;
    void TearDown() override;
    void populate(int count) const;
};

#endif