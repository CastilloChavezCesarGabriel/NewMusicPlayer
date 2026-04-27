#include "RemoveSongUseCaseTest.h"
#include "../SongVisitorSpy.h"
#include "../../model/tracklist/QuickSort.h"
#include <filesystem>
#include <fstream>

std::string RemoveSongUseCaseTest::identify() const {
    return "remove_uc";
}

TEST_F(RemoveSongUseCaseTest, RemoveFirstSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(0);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(2);
}

TEST_F(RemoveSongUseCaseTest, RemoveLastSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(2);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(2);
}

TEST_F(RemoveSongUseCaseTest, RemoveMiddleSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(1);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(2);
}

TEST_F(RemoveSongUseCaseTest, RemoveNotifiesChanged) {
    createSong("a.mp3");
    build();
    library_->remove(0);
    library_spy_.expectChange();
}

TEST_F(RemoveSongUseCaseTest, RemoveReducesPlaylistSize) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    library_->remove(0);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(1);
}

TEST_F(RemoveSongUseCaseTest, RemoveFromEmptyDoesNotCrash) {
    build();
    EXPECT_NO_THROW(library_->remove(0));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenPlay) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    library_->remove(0);
    playback_->play(0);
    track_spy_.expectSelect();
}

TEST_F(RemoveSongUseCaseTest, RemoveOnlySongLeavesEmpty) {
    createSong("only.mp3");
    build();
    library_->remove(0);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectEmpty();
}

TEST_F(RemoveSongUseCaseTest, RemoveAllSongsOneByOne) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(0);
    library_->remove(0);
    library_->remove(0);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectEmpty();
}

TEST_F(RemoveSongUseCaseTest, RemoveThenAdd) {
    createSong("a.mp3");
    build();
    library_->remove(0);
    library_->insert(prepare("b.mp3"));
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(1);
    visitor.expectName("b.mp3");
}

TEST_F(RemoveSongUseCaseTest, RemoveThenSort) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    library_->remove(0);
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(2);
}

TEST_F(RemoveSongUseCaseTest, RemoveThenSearch) {
    createSong("rock.mp3");
    createSong("jazz.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    library_->remove(0);
    SongVisitorSpy visitor;
    catalog_->search("jazz", visitor);
    visitor.expectEmpty();
}

TEST_F(RemoveSongUseCaseTest, RemoveDoesNotStartPlayback) {
    createSong("a.mp3");
    build();
    library_->remove(0);
    track_spy_.expectNoStart();
}

TEST_F(RemoveSongUseCaseTest, RemoveDoesNotSelect) {
    createSong("a.mp3");
    build();
    library_->remove(0);
    track_spy_.expectNoSelect();
}

TEST_F(RemoveSongUseCaseTest, RemoveMultipleNotifiesEachTime) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(0);
    library_->remove(0);
    library_spy_.expectChanges(2);
}

TEST_F(RemoveSongUseCaseTest, RemovePreservesOtherSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    library_->remove(1);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectName("a.mp3");
    visitor.expectName("c.mp3");
}

TEST_F(RemoveSongUseCaseTest, RemoveFirstPreservesRest) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    library_->remove(0);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectName("b.mp3");
}

TEST_F(RemoveSongUseCaseTest, RemoveLastPreservesRest) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    library_->remove(1);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectName("a.mp3");
}

TEST_F(RemoveSongUseCaseTest, RemoveThenPlayRemaining) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(0);
    playback_->play(0);
    track_spy_.expectSelectWith(0);
}

TEST_F(RemoveSongUseCaseTest, RemoveThenAdvance) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(0);
    playback_->play(0);
    playback_->advance();
    track_spy_.expectSelectWith(1);
}

TEST_F(RemoveSongUseCaseTest, RemoveThenRetreat) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(0);
    playback_->play(1);
    playback_->retreat();
    track_spy_.expectSelectWith(0);
}

TEST_F(RemoveSongUseCaseTest, RemoveAllThenAddNew) {
    createSong("a.mp3");
    build();
    library_->remove(0);
    library_->insert(prepare("new.mp3"));
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(1);
}

TEST_F(RemoveSongUseCaseTest, RemoveTwoFromThree) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(0);
    library_->remove(0);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(1);
}

TEST_F(RemoveSongUseCaseTest, RemoveThenSortRemaining) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    library_->remove(0);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectNameAt(0, "b.mp3");
    visitor.expectNameAt(1, "c.mp3");
}

TEST_F(RemoveSongUseCaseTest, RemoveWavFile) {
    createSong("track.wav");
    build();
    library_->remove(0);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectEmpty();
}

TEST_F(RemoveSongUseCaseTest, RemoveNotifiesChangedOnce) {
    createSong("a.mp3");
    build();
    library_->remove(0);
    library_spy_.expectChanges(1);
}

TEST_F(RemoveSongUseCaseTest, RemoveFromFiveSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    createSong("e.mp3");
    build();
    library_->remove(2);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(4);
}

TEST_F(RemoveSongUseCaseTest, RemoveThreeTimesNotifiesThree) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(0);
    library_->remove(0);
    library_->remove(0);
    library_spy_.expectChanges(3);
}

TEST_F(RemoveSongUseCaseTest, RemoveThenSearchFindsRemaining) {
    createSong("rock.mp3");
    createSong("jazz.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    library_->remove(1);
    SongVisitorSpy visitor;
    catalog_->search("jazz", visitor);
    visitor.expectName("jazz.mp3");
}

TEST_F(RemoveSongUseCaseTest, RemoveDoesNotGiveFeedback) {
    createSong("a.mp3");
    build();
    library_->remove(0);
    library_spy_.expectNoFeedback("Song added successfully!");
}