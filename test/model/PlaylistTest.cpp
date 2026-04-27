#include "PlaylistTest.h"
#include "../PathVisitorSpy.h"
#include "../../model/tracklist/DurationSort.h"
#include "../../model/tracklist/QuickSort.h"
#include "../../model/event/ITrackListener.h"
#include "../../model/tracklist/ShuffleStrategy.h"
#include "../../model/tracklist/ReverseStrategy.h"
#include <fstream>

std::string PlaylistTest::identify() const {
    return "playlist_test";
}

void PlaylistTest::SetUp() {
    DirectoryTestFixture::SetUp();
    track_bus_.add(track_spy_);
    tracklist_ = std::make_unique<Tracklist>();
    cursor_ = std::make_unique<TrackCursor>(*tracklist_, track_bus_);
}

void PlaylistTest::TearDown() {
    cursor_.reset();
    tracklist_.reset();
    DirectoryTestFixture::TearDown();
}

void PlaylistTest::populate(const int count) const {
    for (int i = 0; i < count; i++) {
        tracklist_->add(Song("(" + std::to_string(i + 1) + ") Song" + std::to_string(i) + ".mp3",
                          test_directory_ + "/song" + std::to_string(i) + ".mp3"));
    }
}
TEST_F(PlaylistTest, AddSingleSong) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->accept(visitor_);
    visitor_.expectCount(1);
}

TEST_F(PlaylistTest, AddMultipleSongs) {
    populate(5);
    tracklist_->accept(visitor_);
    visitor_.expectCount(5);
}

TEST_F(PlaylistTest, AddPreservesOrder) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    tracklist_->accept(visitor_);
    visitor_.expectNameAt(0, "A.mp3");
    visitor_.expectNameAt(1, "B.mp3");
}

TEST_F(PlaylistTest, RemoveReducesCount) {
    populate(3);
    PathVisitorSpy sink;
    tracklist_->remove(1, sink);
    tracklist_->accept(visitor_);
    visitor_.expectCount(2);
}

TEST_F(PlaylistTest, RemoveFirstSong) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    PathVisitorSpy sink;
    tracklist_->remove(0, sink);
    tracklist_->accept(visitor_);
    visitor_.expectNameAt(0, "B.mp3");
}

TEST_F(PlaylistTest, RemoveLastSong) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    PathVisitorSpy sink;
    tracklist_->remove(1, sink);
    tracklist_->accept(visitor_);
    visitor_.expectCount(1);
    visitor_.expectName("A.mp3");
}

TEST_F(PlaylistTest, RemoveInvalidNegativeIndex) {
    populate(3);
    PathVisitorSpy sink;
    tracklist_->remove(-1, sink);
    tracklist_->accept(visitor_);
    visitor_.expectCount(3);
}

TEST_F(PlaylistTest, RemoveInvalidLargeIndex) {
    populate(3);
    PathVisitorSpy sink;
    tracklist_->remove(100, sink);
    tracklist_->accept(visitor_);
    visitor_.expectCount(3);
}

TEST_F(PlaylistTest, RemoveFromEmptyPlaylist) {
    PathVisitorSpy sink;
    tracklist_->remove(0, sink);
    tracklist_->accept(visitor_);
    visitor_.expectEmpty();
}

TEST_F(PlaylistTest, SortByNameAlphabetical) {
    tracklist_->add(Song("C.mp3", "/c"));
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    QuickSort byName;
    tracklist_->reorder(byName);
    tracklist_->accept(visitor_);
    visitor_.expectNameAt(0, "A.mp3");
    visitor_.expectNameAt(1, "B.mp3");
    visitor_.expectNameAt(2, "C.mp3");
}

TEST_F(PlaylistTest, SortByDurationAscending) {
    const std::string largeTrack = test_directory_ + "/large.mp3";
    const std::string smallTrack = test_directory_ + "/small.mp3";
    const std::string mediumTrack = test_directory_ + "/medium.mp3";
    std::ofstream(largeTrack) << std::string(300, 'x');
    std::ofstream(smallTrack) << std::string(100, 'x');
    std::ofstream(mediumTrack) << std::string(200, 'x');
    tracklist_->add(Song("large.mp3", largeTrack));
    tracklist_->add(Song("small.mp3", smallTrack));
    tracklist_->add(Song("medium.mp3", mediumTrack));
    DurationSort byDuration;
    tracklist_->reorder(byDuration);
    tracklist_->accept(visitor_);
    visitor_.expectNameAt(0, "small.mp3");
    visitor_.expectNameAt(1, "medium.mp3");
    visitor_.expectNameAt(2, "large.mp3");
}

TEST_F(PlaylistTest, SortEmptyPlaylist) {
    QuickSort byName;
    tracklist_->reorder(byName);
    tracklist_->accept(visitor_);
    visitor_.expectEmpty();
}

TEST_F(PlaylistTest, SortSingleSong) {
    tracklist_->add(Song("A.mp3", "/a"));
    QuickSort byName;
    tracklist_->reorder(byName);
    tracklist_->accept(visitor_);
    visitor_.expectCount(1);
}

TEST_F(PlaylistTest, ShuffleDoesNotChangeCount) {
    populate(10);
    ShuffleStrategy strat;
    tracklist_->reorder(strat);
    tracklist_->accept(visitor_);
    visitor_.expectCount(10);
}

TEST_F(PlaylistTest, ShufflePreservesSelection) {
    populate(5);
    cursor_->select(2);
    cursor_->chase([&] {
        ShuffleStrategy strat;
        tracklist_->reorder(strat);
    });
    cursor_->play();
    track_spy_.expectStartWith(test_directory_ + "/song2.mp3");
}

TEST_F(PlaylistTest, SelectValidIndex) {
    populate(3);
    cursor_->select(1);
    EXPECT_TRUE(cursor_->hasSelected());
    track_spy_.expectSelectWith(1);
}

TEST_F(PlaylistTest, SelectInvalidNegativeIndex) {
    populate(3);
    cursor_->select(-1);
    EXPECT_FALSE(cursor_->hasSelected());
}

TEST_F(PlaylistTest, SelectInvalidLargeIndex) {
    populate(3);
    cursor_->select(100);
    EXPECT_FALSE(cursor_->hasSelected());
}

TEST_F(PlaylistTest, AdvanceMovesToNext) {
    populate(3);
    cursor_->select(0);
    cursor_->advance();
    track_spy_.expectSelectWith(1);
}

TEST_F(PlaylistTest, AdvanceAtEndDoesNothing) {
    populate(3);
    cursor_->select(2);
    cursor_->advance();
    track_spy_.expectNoSelectWith(3);
}

TEST_F(PlaylistTest, RetreatMovesToPrevious) {
    populate(3);
    cursor_->select(2);
    cursor_->retreat();
    track_spy_.expectSelectWith(1);
}

TEST_F(PlaylistTest, RetreatAtStartDoesNothing) {
    populate(3);
    cursor_->select(0);
    cursor_->retreat();
    track_spy_.expectNoSelectWith(-1);
}

TEST_F(PlaylistTest, PlayCurrentSong) {
    tracklist_->add(Song("A.mp3", "/a"));
    cursor_->select(0);
    cursor_->play();
    track_spy_.expectStartWith("/a");
}

TEST_F(PlaylistTest, PlayWithNoSelection) {
    populate(3);
    cursor_->play();
    track_spy_.expectNoStart();
}

TEST_F(PlaylistTest, SearchFindsMatchingSongs) {
    tracklist_->add(Song("Hello.mp3", "/a"));
    tracklist_->add(Song("Goodbye.mp3", "/b"));
    tracklist_->add(Song("Hello World.mp3", "/c"));
    tracklist_->filter("Hello", visitor_);
    visitor_.expectCount(2);
}

TEST_F(PlaylistTest, SearchReturnsEmptyForNoMatch) {
    populate(5);
    tracklist_->filter("ZZZZZ", visitor_);
    visitor_.expectEmpty();
}

TEST_F(PlaylistTest, SearchEmptyQueryReturnsAll) {
    populate(3);
    tracklist_->filter("", visitor_);
    visitor_.expectCount(3);
}

TEST_F(PlaylistTest, HasNextWhenMoreSongsExist) {
    populate(3);
    cursor_->select(0);
    EXPECT_TRUE(cursor_->hasNext());
}

TEST_F(PlaylistTest, HasNextFalseAtEnd) {
    populate(3);
    cursor_->select(2);
    EXPECT_FALSE(cursor_->hasNext());
}

TEST_F(PlaylistTest, HasSelectedFalseInitially) {
    populate(3);
    EXPECT_FALSE(cursor_->hasSelected());
}

TEST_F(PlaylistTest, HasSelectedTrueAfterSelect) {
    populate(3);
    cursor_->select(1);
    EXPECT_TRUE(cursor_->hasSelected());
}

TEST_F(PlaylistTest, RemoveCurrentSongResetsSelection) {
    populate(3);
    cursor_->select(1);
    PathVisitorSpy sink;
    tracklist_->remove(1, sink);
    EXPECT_FALSE(cursor_->hasSelected());
}

TEST_F(PlaylistTest, RemoveBeforeCurrentAdjustsIndex) {
    populate(5);
    cursor_->select(3);
    PathVisitorSpy sink;
    tracklist_->remove(0, sink);
    cursor_->play();
    track_spy_.expectStartWith(test_directory_ + "/song3.mp3");
}

TEST_F(PlaylistTest, AcceptEmptyPlaylist) {
    tracklist_->accept(visitor_);
    visitor_.expectEmpty();
}

TEST_F(PlaylistTest, AcceptAllSongs) {
    populate(4);
    tracklist_->accept(visitor_);
    visitor_.expectCount(4);
}

TEST_F(PlaylistTest, SelectNotifiesListener) {
    populate(3);
    cursor_->select(2);
    track_spy_.expectSelect();
}

TEST_F(PlaylistTest, AdvanceNotifiesListener) {
    populate(3);
    cursor_->select(0);
    cursor_->advance();
    track_spy_.expectSelectWith(1);
}

TEST_F(PlaylistTest, RetreatNotifiesListener) {
    populate(3);
    cursor_->select(2);
    cursor_->retreat();
    track_spy_.expectSelectWith(1);
}

TEST_F(PlaylistTest, ReverseInvertsOrder) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    tracklist_->add(Song("C.mp3", "/c"));
    ReverseStrategy strat;
    tracklist_->reorder(strat);
    tracklist_->accept(visitor_);
    visitor_.expectNameAt(0, "C.mp3");
    visitor_.expectNameAt(1, "B.mp3");
    visitor_.expectNameAt(2, "A.mp3");
}

TEST_F(PlaylistTest, ReverseEmptyPlaylist) {
    ReverseStrategy strat;
    tracklist_->reorder(strat);
    tracklist_->accept(visitor_);
    visitor_.expectEmpty();
}

TEST_F(PlaylistTest, ReversePreservesCurrentSong) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    tracklist_->add(Song("C.mp3", "/c"));
    cursor_->select(0);
    cursor_->chase([&] {
        ReverseStrategy strat;
        tracklist_->reorder(strat);
    });
    cursor_->retreat();
    track_spy_.expectSelectWith(1);
}

TEST_F(PlaylistTest, RestoreReturnsOriginalOrder) {
    tracklist_->add(Song("C.mp3", "/c"));
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    QuickSort byName;
    tracklist_->reorder(byName);
    tracklist_->restore();
    tracklist_->accept(visitor_);
    visitor_.expectNameAt(0, "C.mp3");
    visitor_.expectNameAt(1, "A.mp3");
    visitor_.expectNameAt(2, "B.mp3");
}

TEST_F(PlaylistTest, RestoreDoesNothingWhenNothingPreserved) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    tracklist_->restore();
    tracklist_->accept(visitor_);
    visitor_.expectNameAt(0, "A.mp3");
    visitor_.expectNameAt(1, "B.mp3");
}

TEST_F(PlaylistTest, RestorePreservesCurrentSong) {
    tracklist_->add(Song("C.mp3", "/c"));
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    cursor_->select(0);
    QuickSort byName;
    cursor_->chase([&] {
        tracklist_->reorder(byName);
    });
    cursor_->chase([&] {
        tracklist_->restore();
    });
    cursor_->advance();
    track_spy_.expectSelectWith(1);
}

TEST_F(PlaylistTest, SortReverseRestoreFullCycle) {
    tracklist_->add(Song("C.mp3", "/c"));
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    QuickSort byName;
    tracklist_->reorder(byName);
    ReverseStrategy revStrat;
    tracklist_->reorder(revStrat);
    tracklist_->restore();
    tracklist_->accept(visitor_);
    visitor_.expectNameAt(0, "C.mp3");
    visitor_.expectNameAt(1, "A.mp3");
    visitor_.expectNameAt(2, "B.mp3");
}