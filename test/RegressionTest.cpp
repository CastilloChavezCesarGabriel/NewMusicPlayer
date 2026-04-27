#include "RegressionTest.h"
#include "../model/song/Song.h"
#include "../model/tracklist/Tracklist.h"
#include "../model/tracklist/TrackCursor.h"
#include "../model/event/TrackBus.h"
#include "../model/event/AdBus.h"
#include "../model/library/Dice.h"
#include "../model/playback/RandomAdPolicy.h"
#include "../model/tracklist/DurationSort.h"
#include "../model/tracklist/QuickSort.h"
#include "../model/tracklist/ShuffleStrategy.h"
#include "SongVisitorSpy.h"
#include "PathVisitorSpy.h"
#include <filesystem>
#include <fstream>

std::string RegressionTest::identify() const {
    return "regression_test";
}

TEST_F(RegressionTest, SortEmptyPlaylistDoesNotCrash) {
    Tracklist tracklist;
    QuickSort byName;
    EXPECT_NO_THROW(tracklist.reorder(byName));
}

TEST_F(RegressionTest, SortSingleSongDoesNotCrash) {
    Tracklist tracklist;
    tracklist.add(Song("A.mp3", "/a"));
    QuickSort byName;
    EXPECT_NO_THROW(tracklist.reorder(byName));
}

TEST_F(RegressionTest, ShellSortEmptyDoesNotCrash) {
    Tracklist tracklist;
    DurationSort byNumber;
    EXPECT_NO_THROW(tracklist.reorder(byNumber));
}

TEST_F(RegressionTest, ModelRefreshDoesNotRecurse) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    EXPECT_NO_THROW(setlist_->sort(byTitle));
    setlist_->announce();
    library_spy_.expectChange();
}

TEST_F(RegressionTest, ModelSortByNameDoesNotCrash) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    EXPECT_NO_THROW(setlist_->sort(byTitle));
}

TEST_F(RegressionTest, ModelSortByNumberDoesNotCrash) {
    createSong("(3) C.mp3");
    createSong("(1) A.mp3");
    createSong("(2) B.mp3");
    build();
    DurationSort byDuration;
    EXPECT_NO_THROW(setlist_->sort(byDuration));
}

TEST_F(RegressionTest, AdvanceUpdatesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    track_spy_.expectSelectWith(1);
}

TEST_F(RegressionTest, RetreatUpdatesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(2);
    playback_->retreat();
    track_spy_.expectSelectWith(1);
}

TEST_F(RegressionTest, RemoveBeforeCurrentAdjustsSelection) {
    TrackBus trackBus;
    Tracklist tracklist;
    TrackCursor cursor(tracklist, trackBus);
    tracklist.add(Song("A.mp3", "/a"));
    tracklist.add(Song("B.mp3", "/b"));
    tracklist.add(Song("C.mp3", "/c"));
    cursor.select(2);
    PathVisitorSpy sink;
    tracklist.remove(0, sink);
    EXPECT_TRUE(cursor.hasSelected());
}

TEST_F(RegressionTest, QuickSortPartitionDoesNotUnderflow) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    QuickSort sorter;
    EXPECT_NO_THROW(sorter.arrange(songs));
}

TEST_F(RegressionTest, InsertUnsupportedFileGivesFeedback) {
    build();
    library_->insert("");
    library_spy_.expectFeedback("Unsupported file type.");
}

TEST_F(RegressionTest, InsertDuplicateGivesFeedback) {
    createSong("dup.mp3");
    build();
    library_->insert(prepare("dup.mp3"));
    library_spy_.expectFeedback("This song already exists.");
}

TEST_F(RegressionTest, SortPreservesAllSongs) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(3);
}

TEST_F(RegressionTest, ShufflePreservesAllSongs) {
    Tracklist tracklist;
    for (int i = 0; i < 20; i++) {
        tracklist.add(Song(std::to_string(i) + ".mp3", "/s"));
    }
    ShuffleStrategy strat;
    tracklist.reorder(strat);
    SongVisitorSpy visitor;
    tracklist.accept(visitor);
    visitor.expectCount(20);
}

TEST_F(RegressionTest, RepeatCycles) {
    build();
    repeat_policy_->advance();
    repeat_policy_->advance();
    repeat_policy_->advance();
    EXPECT_NO_THROW(repeat_policy_->advance());
}

TEST_F(RegressionTest, RemoveFromEmptyPlaylistDoesNotCrash) {
    Tracklist tracklist;
    PathVisitorSpy sink;
    EXPECT_NO_THROW(tracklist.remove(0, sink));
}

TEST_F(RegressionTest, RemoveNegativeIndexDoesNotCrash) {
    Tracklist tracklist;
    tracklist.add(Song("A.mp3", "/a"));
    PathVisitorSpy sink;
    EXPECT_NO_THROW(tracklist.remove(-1, sink));
}

TEST_F(RegressionTest, SelectInvalidIndexDoesNotCrash) {
    TrackBus trackBus;
    Tracklist tracklist;
    TrackCursor cursor(tracklist, trackBus);
    EXPECT_NO_THROW(cursor.select(999));
}

TEST_F(RegressionTest, PlayWithNoSelectionDoesNotCrash) {
    TrackBus trackBus;
    Tracklist tracklist;
    TrackCursor cursor(tracklist, trackBus);
    tracklist.add(Song("A.mp3", "/a"));
    EXPECT_NO_THROW(cursor.play());
}

TEST_F(RegressionTest, ConcludeWithoutInterruptReturnsFalse) {
    Dice dice;
    RandomAdPolicy adPolicy(dice);
    AdBus adBus;
    TrackBus trackBus;
    adBus.add(ad_spy_);
    trackBus.add(track_spy_);
    AdScheduler ad(adPolicy, adBus, trackBus);
    ad.load(ads_directory_);
    EXPECT_FALSE(ad.conclude());
}

TEST_F(RegressionTest, MultipleSortsDoNotCrash) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            QuickSort byTitle;
            EXPECT_NO_THROW(setlist_->sort(byTitle));
        } else {
            DurationSort byDuration;
            EXPECT_NO_THROW(setlist_->sort(byDuration));
        }
    }
}

TEST_F(RegressionTest, SortThenAdvanceWorks) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    playback_->play(0);
    EXPECT_NO_THROW(playback_->advance());
}

TEST_F(RegressionTest, LargePlaylistSortDoesNotCrash) {
    Tracklist tracklist;
    for (int i = 500; i > 0; i--) {
        tracklist.add(Song("(" + std::to_string(i) + ") Song.mp3", "/s"));
    }
    DurationSort byNumber;
    EXPECT_NO_THROW(tracklist.reorder(byNumber));
    QuickSort byName;
    EXPECT_NO_THROW(tracklist.reorder(byName));
}