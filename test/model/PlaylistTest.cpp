#include "PlaylistTest.h"
#include "../../model/DurationSort.h"
#include "../../model/QuickSort.h"
#include "../../model/ITrackListener.h"
#include "../../model/ShuffleArrangement.h"
#include "../../model/ReverseArrangement.h"
#include <filesystem>
#include <fstream>

void PlaylistTest::SetUp() {
    test_directory_ = std::filesystem::temp_directory_path().string() + "/playlist_test";
    std::filesystem::create_directories(test_directory_);
    track_bus_.add(listener_);
    tracklist_ = std::make_unique<Tracklist>();
    cursor_ = std::make_unique<Cursor>(*tracklist_, track_bus_);
}

void PlaylistTest::TearDown() {
    cursor_.reset();
    tracklist_.reset();
    std::filesystem::remove_all(test_directory_);
}

void PlaylistTest::populate(int count) const {
    for (int i = 0; i < count; i++) {
        tracklist_->add(Song("(" + std::to_string(i + 1) + ") Song" + std::to_string(i) + ".mp3",
                          test_directory_ + "/song" + std::to_string(i) + ".mp3"));
    }
}

TEST_F(PlaylistTest, AddSingleSong) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(1));
}

TEST_F(PlaylistTest, AddMultipleSongs) {
    populate(5);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(5));
}

TEST_F(PlaylistTest, AddPreservesOrder) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
}

TEST_F(PlaylistTest, RemoveReducesCount) {
    populate(3);
    TestPlaylistVisitor sink;
    tracklist_->discard(1, sink);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(2));
}

TEST_F(PlaylistTest, RemoveFirstSong) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    TestPlaylistVisitor sink;
    tracklist_->discard(0, sink);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "B.mp3"));
}

TEST_F(PlaylistTest, RemoveLastSong) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    TestPlaylistVisitor sink;
    tracklist_->discard(1, sink);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(1));
    EXPECT_TRUE(visitor_.hasName("A.mp3"));
}

TEST_F(PlaylistTest, RemoveInvalidNegativeIndex) {
    populate(3);
    TestPlaylistVisitor sink;
    tracklist_->discard(-1, sink);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(3));
}

TEST_F(PlaylistTest, RemoveInvalidLargeIndex) {
    populate(3);
    TestPlaylistVisitor sink;
    tracklist_->discard(100, sink);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(3));
}

TEST_F(PlaylistTest, RemoveFromEmptyPlaylist) {
    TestPlaylistVisitor sink;
    tracklist_->discard(0, sink);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, SortByNameAlphabetical) {
    tracklist_->add(Song("C.mp3", "/c"));
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    QuickSort byName;
    tracklist_->arrange(byName);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "C.mp3"));
}

TEST_F(PlaylistTest, SortByDurationAscending) {
    const std::string large = test_directory_ + "/large.mp3";
    const std::string small = test_directory_ + "/small.mp3";
    const std::string medium = test_directory_ + "/medium.mp3";
    std::ofstream(large) << std::string(300, 'x');
    std::ofstream(small) << std::string(100, 'x');
    std::ofstream(medium) << std::string(200, 'x');
    tracklist_->add(Song("large.mp3", large));
    tracklist_->add(Song("small.mp3", small));
    tracklist_->add(Song("medium.mp3", medium));
    DurationSort byDuration;
    tracklist_->arrange(byDuration);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "small.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "medium.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "large.mp3"));
}

TEST_F(PlaylistTest, SortEmptyPlaylist) {
    QuickSort byName;
    tracklist_->arrange(byName);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, SortSingleSong) {
    tracklist_->add(Song("A.mp3", "/a"));
    QuickSort byName;
    tracklist_->arrange(byName);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(1));
}

TEST_F(PlaylistTest, ShuffleDoesNotChangeCount) {
    populate(10);
    ShuffleArrangement strat;
    tracklist_->arrange(strat);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(10));
}

TEST_F(PlaylistTest, ShufflePreservesSelection) {
    populate(5);
    cursor_->select(2);
    cursor_->pin([&] {
        ShuffleArrangement strat;
        tracklist_->arrange(strat);
    });
    EXPECT_TRUE(cursor_->hasSelected());
}

TEST_F(PlaylistTest, ClearRemovesAllSongs) {
    populate(5);
    tracklist_->clear();
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, ClearResetsSelection) {
    populate(5);
    cursor_->select(2);
    tracklist_->clear();
    cursor_->clear();
    EXPECT_FALSE(cursor_->hasSelected());
}

TEST_F(PlaylistTest, SelectValidIndex) {
    populate(3);
    cursor_->select(1);
    EXPECT_TRUE(cursor_->hasSelected());
    EXPECT_TRUE(listener_.wasSelectedWith(1));
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
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, AdvanceAtEndDoesNothing) {
    populate(3);
    cursor_->select(2);
    cursor_->advance();
    EXPECT_FALSE(listener_.wasSelectedWith(3));
}

TEST_F(PlaylistTest, RetreatMovesToPrevious) {
    populate(3);
    cursor_->select(2);
    cursor_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, RetreatAtStartDoesNothing) {
    populate(3);
    cursor_->select(0);
    cursor_->retreat();
    EXPECT_FALSE(listener_.wasSelectedWith(-1));
}

TEST_F(PlaylistTest, PlayCurrentSong) {
    tracklist_->add(Song("A.mp3", "/a"));
    cursor_->select(0);
    cursor_->play();
    EXPECT_TRUE(listener_.wasStartedWith("/a"));
}

TEST_F(PlaylistTest, PlayWithNoSelection) {
    populate(3);
    cursor_->play();
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(PlaylistTest, SearchFindsMatchingSongs) {
    tracklist_->add(Song("Hello.mp3", "/a"));
    tracklist_->add(Song("Goodbye.mp3", "/b"));
    tracklist_->add(Song("Hello World.mp3", "/c"));
    tracklist_->search("Hello", visitor_);
    EXPECT_TRUE(visitor_.hasSongs(2));
}

TEST_F(PlaylistTest, SearchReturnsEmptyForNoMatch) {
    populate(5);
    tracklist_->search("ZZZZZ", visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, SearchEmptyQueryReturnsAll) {
    populate(3);
    tracklist_->search("", visitor_);
    EXPECT_TRUE(visitor_.hasSongs(3));
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
    TestPlaylistVisitor sink;
    tracklist_->discard(1, sink);
    EXPECT_FALSE(cursor_->hasSelected());
}

TEST_F(PlaylistTest, RemoveBeforeCurrentAdjustsIndex) {
    populate(5);
    cursor_->select(3);
    TestPlaylistVisitor sink;
    tracklist_->discard(0, sink);
    cursor_->play();
    EXPECT_TRUE(listener_.wasStartedWith(test_directory_ + "/song3.mp3"));
}

TEST_F(PlaylistTest, AcceptEmptyPlaylist) {
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, AcceptAllSongs) {
    populate(4);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(4));
}

TEST_F(PlaylistTest, SelectNotifiesListener) {
    populate(3);
    cursor_->select(2);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaylistTest, AdvanceNotifiesListener) {
    populate(3);
    cursor_->select(0);
    cursor_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, RetreatNotifiesListener) {
    populate(3);
    cursor_->select(2);
    cursor_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, ReverseInvertsOrder) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    tracklist_->add(Song("C.mp3", "/c"));
    ReverseArrangement strat;
    tracklist_->arrange(strat);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "C.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "A.mp3"));
}

TEST_F(PlaylistTest, ReverseEmptyPlaylist) {
    ReverseArrangement strat;
    tracklist_->arrange(strat);
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, ReversePreservesCurrentSong) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    tracklist_->add(Song("C.mp3", "/c"));
    cursor_->select(0);
    cursor_->pin([&] {
        ReverseArrangement strat;
        tracklist_->arrange(strat);
    });
    cursor_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, RestoreReturnsOriginalOrder) {
    tracklist_->add(Song("C.mp3", "/c"));
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    QuickSort byName;
    tracklist_->arrange(byName);
    tracklist_->restore();
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "C.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "B.mp3"));
}

TEST_F(PlaylistTest, RestoreDoesNothingWhenNothingPreserved) {
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    tracklist_->restore();
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
}

TEST_F(PlaylistTest, RestorePreservesCurrentSong) {
    tracklist_->add(Song("C.mp3", "/c"));
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    cursor_->select(0);
    QuickSort byName;
    cursor_->pin([&] {
        tracklist_->arrange(byName);
    });
    cursor_->pin([&] {
        tracklist_->restore();
    });
    cursor_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, SortReverseRestoreFullCycle) {
    tracklist_->add(Song("C.mp3", "/c"));
    tracklist_->add(Song("A.mp3", "/a"));
    tracklist_->add(Song("B.mp3", "/b"));
    QuickSort byName;
    tracklist_->arrange(byName);
    ReverseArrangement revStrat;
    tracklist_->arrange(revStrat);
    tracklist_->restore();
    tracklist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "C.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "B.mp3"));
}
