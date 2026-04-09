#include "NavigatePlaylistUseCaseTest.h"
#include "../TestPlaylistVisitor.h"
#include "../../model/QuickSort.h"
#include <filesystem>
#include <fstream>

std::string NavigatePlaylistUseCaseTest::identify() const {
    return "navigate_uc";
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceFromFirstToSecond) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceFromMiddle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(1);
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceAtEndDoesNotCrash) {
    createSong("a.mp3");
    build();
    playback_->play(0);
    EXPECT_NO_THROW(playback_->advance());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatFromLastToMiddle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(2);
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatFromMiddleToFirst) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(1);
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatAtStartDoesNotCrash) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    EXPECT_NO_THROW(playback_->retreat());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceThenRetreatReturnsToStart) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceThroughAll) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatThroughAll) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(2);
    playback_->retreat();
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(1);
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceNotifiesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatNotifiesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(1);
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceAfterSort) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    playback_->play(0);
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatAfterSort) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    playback_->play(2);
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceAfterRemove) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(0);
    playback_->play(0);
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatAfterRemove) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(0);
    playback_->play(1);
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceAfterInsert) {
    createSong("a.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    build();
    library_->insert(srcDir + "/b.mp3");
    playback_->play(0);
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatAfterInsert) {
    createSong("a.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    build();
    library_->insert(srcDir + "/b.mp3");
    playback_->play(1);
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceMultipleTimes) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    playback_->advance();
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(3));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatMultipleTimes) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    build();
    playback_->play(3);
    playback_->retreat();
    playback_->retreat();
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceThenRetreatThenAdvance) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    playback_->retreat();
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceOnSingleSongDoesNotCrash) {
    createSong("only.mp3");
    build();
    playback_->play(0);
    EXPECT_NO_THROW(playback_->advance());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatOnSingleSongDoesNotCrash) {
    createSong("only.mp3");
    build();
    playback_->play(0);
    EXPECT_NO_THROW(playback_->retreat());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceTwoSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatTwoSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(1);
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceFiveSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    createSong("e.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    playback_->advance();
    playback_->advance();
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(4));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceDoesNotNotifyChanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatDoesNotNotifyChanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(1);
    playback_->retreat();
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceThenPlaylistUnchanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceSortedPlaylist) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    playback_->play(0);
    playback_->advance();
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatSortedPlaylist) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    playback_->play(2);
    playback_->retreat();
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}
