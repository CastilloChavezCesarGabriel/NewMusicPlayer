#include "SortPlaylistUseCaseTest.h"
#include "../SongVisitorSpy.h"
#include "../../model/tracklist/QuickSort.h"
#include "../../model/tracklist/DurationSort.h"
#include <filesystem>
#include <fstream>

std::string SortPlaylistUseCaseTest::identify() const {
    return "sort_uc";
}

TEST_F(SortPlaylistUseCaseTest, SortByNameNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    setlist_->announce();
    library_spy_.expectChange();
}

TEST_F(SortPlaylistUseCaseTest, SortByNumberNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    build();
    DurationSort byDuration;
    setlist_->sort(byDuration);
    setlist_->announce();
    library_spy_.expectChange();
}

TEST_F(SortPlaylistUseCaseTest, SortByNameOrdersAlphabetically) {
    createSong("cherry.mp3");
    createSong("apple.mp3");
    createSong("banana.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectNameAt(0, "apple.mp3");
    visitor.expectNameAt(1, "banana.mp3");
    visitor.expectNameAt(2, "cherry.mp3");
}

TEST_F(SortPlaylistUseCaseTest, SortEmptyPlaylistDoesNotCrash) {
    build();
    QuickSort byTitle;
    EXPECT_NO_THROW(setlist_->sort(byTitle));
}

TEST_F(SortPlaylistUseCaseTest, SortEmptyPlaylistNotifiesChanged) {
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    setlist_->announce();
    library_spy_.expectChange();
}

TEST_F(SortPlaylistUseCaseTest, SortSingleSongDoesNotCrash) {
    createSong("only.mp3");
    build();
    QuickSort byTitle;
    EXPECT_NO_THROW(setlist_->sort(byTitle));
}

TEST_F(SortPlaylistUseCaseTest, SortSingleSongPreserves) {
    createSong("only.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectName("only.mp3");
    visitor.expectCount(1);
}

TEST_F(SortPlaylistUseCaseTest, SortPreservesSongCount) {
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

TEST_F(SortPlaylistUseCaseTest, SortPreservesAllSongNames) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectName("a.mp3");
    visitor.expectName("b.mp3");
    visitor.expectName("c.mp3");
}

TEST_F(SortPlaylistUseCaseTest, SortThenPlayFirstSong) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    playback_->play(0);
    track_spy_.expectSelect();
}

TEST_F(SortPlaylistUseCaseTest, SortThenPlaySelectsCorrectIndex) {
    createSong("c.mp3");
    createSong("a.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    playback_->play(0);
    track_spy_.expectSelectWith(0);
}

TEST_F(SortPlaylistUseCaseTest, SortThenAdvance) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    playback_->play(0);
    playback_->advance();
    track_spy_.expectSelectWith(1);
}

TEST_F(SortPlaylistUseCaseTest, SortThenRetreat) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    playback_->play(1);
    playback_->retreat();
    track_spy_.expectSelectWith(0);
}

TEST_F(SortPlaylistUseCaseTest, SortMultipleTimesDoesNotCrash) {
    createSong("b.mp3");
    createSong("a.mp3");
    build();
    QuickSort byTitle;
    EXPECT_NO_THROW(setlist_->sort(byTitle));
    DurationSort byDuration;
    EXPECT_NO_THROW(setlist_->sort(byDuration));
    EXPECT_NO_THROW(setlist_->sort(byTitle));
}

TEST_F(SortPlaylistUseCaseTest, SortMultipleTimesNotifiesEachTime) {
    createSong("b.mp3");
    createSong("a.mp3");
    build();
    QuickSort byTitle;
    DurationSort byDuration;
    setlist_->sort(byTitle);
    setlist_->announce();
    setlist_->sort(byDuration);
    setlist_->announce();
    setlist_->sort(byTitle);
    setlist_->announce();
    library_spy_.expectChanges(3);
}

TEST_F(SortPlaylistUseCaseTest, SortAlreadySortedPreservesOrder) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectNameAt(0, "a.mp3");
    visitor.expectNameAt(1, "b.mp3");
    visitor.expectNameAt(2, "c.mp3");
}

TEST_F(SortPlaylistUseCaseTest, SortByNumberDoesNotCrash) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    DurationSort byDuration;
    EXPECT_NO_THROW(setlist_->sort(byDuration));
}

TEST_F(SortPlaylistUseCaseTest, SortByNumberPreservesSongCount) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    DurationSort byDuration;
    setlist_->sort(byDuration);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(3);
}

TEST_F(SortPlaylistUseCaseTest, SortAfterInsert) {
    createSong("c.mp3");
    createSong("a.mp3");
    build();
    library_->insert(prepare("b.mp3"));
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectNameAt(0, "a.mp3");
    visitor.expectNameAt(1, "b.mp3");
    visitor.expectNameAt(2, "c.mp3");
}

TEST_F(SortPlaylistUseCaseTest, SortAfterRemove) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    library_->remove(1);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(2);
    visitor.expectName("a.mp3");
    visitor.expectName("c.mp3");
}

TEST_F(SortPlaylistUseCaseTest, SortByNameThenByNumber) {
    createSong("b.mp3");
    createSong("a.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    DurationSort byDuration;
    setlist_->sort(byDuration);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(2);
}

TEST_F(SortPlaylistUseCaseTest, SortByNameTwoSongs) {
    createSong("z.mp3");
    createSong("a.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectNameAt(0, "a.mp3");
    visitor.expectNameAt(1, "z.mp3");
}

TEST_F(SortPlaylistUseCaseTest, SortFiveSongsByName) {
    createSong("e.mp3");
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("d.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectNameAt(0, "a.mp3");
    visitor.expectNameAt(1, "b.mp3");
    visitor.expectNameAt(2, "c.mp3");
    visitor.expectNameAt(3, "d.mp3");
    visitor.expectNameAt(4, "e.mp3");
}

TEST_F(SortPlaylistUseCaseTest, SortThenAcceptVisitsAll) {
    createSong("b.mp3");
    createSong("a.mp3");
    createSong("c.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectNotEmpty();
    visitor.expectCount(3);
}

TEST_F(SortPlaylistUseCaseTest, SortDoesNotAffectPlayback) {
    createSong("b.mp3");
    createSong("a.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    track_spy_.expectNoStart();
}

TEST_F(SortPlaylistUseCaseTest, SortDoesNotSelect) {
    createSong("b.mp3");
    createSong("a.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    track_spy_.expectNoSelect();
}

TEST_F(SortPlaylistUseCaseTest, SortThenPlayThenAdvanceThroughAll) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    playback_->play(0);
    playback_->advance();
    playback_->advance();
    track_spy_.expectSelectWith(2);
}

TEST_F(SortPlaylistUseCaseTest, SortWavFiles) {
    createSong("b.wav");
    createSong("a.wav");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectNameAt(0, "a.wav");
    visitor.expectNameAt(1, "b.wav");
}

TEST_F(SortPlaylistUseCaseTest, SortMixedExtensions) {
    createSong("b.wav");
    createSong("a.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(2);
}

TEST_F(SortPlaylistUseCaseTest, SortSingleSongNotifiesChanged) {
    createSong("only.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    setlist_->announce();
    library_spy_.expectChanges(1);
}

TEST_F(SortPlaylistUseCaseTest, SortThenSearchFindsCorrectly) {
    createSong("cherry.mp3");
    createSong("apple.mp3");
    createSong("banana.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->search("apple", visitor);
    visitor.expectName("apple.mp3");
}