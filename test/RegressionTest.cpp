#include "RegressionTest.h"
#include "../model/Song.h"
#include "../model/Playlist.h"
#include "../model/MusicLibrary.h"
#include "../model/PlaybackNotifier.h"
#include "../model/Dice.h"
#include "../model/DurationSort.h"
#include "../model/QuickSort.h"
#include "TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

std::string RegressionTest::identify() const {
    return "regression_test";
}

TEST_F(RegressionTest, SortEmptyPlaylistDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    PlaybackNotifier notifier;
    Playlist playlist(lib, notifier);
    QuickSort byName;
    EXPECT_NO_THROW(playlist.sort(byName));
}

TEST_F(RegressionTest, SortSingleSongDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    PlaybackNotifier notifier;
    Playlist playlist(lib, notifier);
    playlist.add(Song("A.mp3", "/a"));
    QuickSort byName;
    EXPECT_NO_THROW(playlist.sort(byName));
}

TEST_F(RegressionTest, ShellSortEmptyDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    PlaybackNotifier notifier;
    Playlist playlist(lib, notifier);
    DurationSort byNumber;
    EXPECT_NO_THROW(playlist.sort(byNumber));
}

TEST_F(RegressionTest, ModelRefreshDoesNotRecurse) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    EXPECT_NO_THROW(setlist_->sort(byTitle));
    EXPECT_TRUE(listener_.wasChanged());
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
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(RegressionTest, RetreatUpdatesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(2);
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(RegressionTest, RemoveBeforeCurrentAdjustsSelection) {
    MusicLibrary lib(music_directory_);
    PlaybackNotifier notifier;
    Playlist playlist(lib, notifier);
    playlist.add(Song("A.mp3", "/a"));
    playlist.add(Song("B.mp3", "/b"));
    playlist.add(Song("C.mp3", "/c"));
    playlist.select(2);
    playlist.remove(0);
    EXPECT_TRUE(playlist.hasSelected());
}

TEST_F(RegressionTest, QuickSortPartitionDoesNotUnderflow) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    QuickSort sorter;
    EXPECT_NO_THROW(sorter.sort(songs));
}

TEST_F(RegressionTest, InsertUnsupportedFileGivesFeedback) {
    build();
    library_->insert("");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(RegressionTest, InsertDuplicateGivesFeedback) {
    createSong("dup.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/dup.mp3") << "data";

    build();
    library_->insert(srcDir + "/dup.mp3");
    EXPECT_TRUE(listener_.wasFeedback("This song already exists."));
}

TEST_F(RegressionTest, SortPreservesAllSongs) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(RegressionTest, ShufflePreservesAllSongs) {
    MusicLibrary lib(music_directory_);
    PlaybackNotifier notifier;
    Playlist playlist(lib, notifier);
    for (int i = 0; i < 20; i++) {
        playlist.add(Song(std::to_string(i) + ".mp3", "/s"));
    }
    playlist.shuffle();
    TestPlaylistVisitor visitor;
    playlist.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(20));
}

TEST_F(RegressionTest, RepeatCycles) {
    build();
    repeat_switch_->cycle();
    repeat_switch_->cycle();
    repeat_switch_->cycle();
    EXPECT_NO_THROW(repeat_switch_->cycle());
}

TEST_F(RegressionTest, RemoveFromEmptyPlaylistDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    PlaybackNotifier notifier;
    Playlist playlist(lib, notifier);
    EXPECT_NO_THROW(playlist.remove(0));
}

TEST_F(RegressionTest, RemoveNegativeIndexDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    PlaybackNotifier notifier;
    Playlist playlist(lib, notifier);
    playlist.add(Song("A.mp3", "/a"));
    EXPECT_NO_THROW(playlist.remove(-1));
}

TEST_F(RegressionTest, SelectInvalidIndexDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    PlaybackNotifier notifier;
    Playlist playlist(lib, notifier);
    EXPECT_NO_THROW(playlist.select(999));
}

TEST_F(RegressionTest, PlayWithNoSelectionDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    PlaybackNotifier notifier;
    Playlist playlist(lib, notifier);
    playlist.add(Song("A.mp3", "/a"));
    EXPECT_NO_THROW(playlist.play());
}

TEST_F(RegressionTest, ConcludeWithoutInterruptReturnsFalse) {
    Dice dice;
    PlaybackNotifier notifier;
    notifier.add(listener_);
    Advertisement ad(ads_directory_, dice, notifier);
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
    MusicLibrary lib(music_directory_);
    PlaybackNotifier notifier;
    Playlist playlist(lib, notifier);
    for (int i = 500; i > 0; i--) {
        playlist.add(Song("(" + std::to_string(i) + ") Song.mp3", "/s"));
    }
    DurationSort byNumber;
    EXPECT_NO_THROW(playlist.sort(byNumber));
    QuickSort byName;
    EXPECT_NO_THROW(playlist.sort(byName));
}
