#include "ModelTest.h"
#include "../SongVisitorSpy.h"
#include "../../model/tracklist/QuickSort.h"
#include "../../model/tracklist/DurationSort.h"
#include "../../model/tracklist/DateSort.h"

std::string ModelTest::identify() const {
    return "model_test";
}

TEST_F(ModelTest, LoadsSongsFromDirectory) {
    createSong("(1) First.mp3");
    createSong("(2) Second.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(2);
}

TEST_F(ModelTest, LoadsEmptyDirectory) {
    build();
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectEmpty();
}

TEST_F(ModelTest, PlaySelectsAndStartsSong) {
    createSong("song.mp3");
    build();
    playback_->play(0);
    track_spy_.expectSelect();
}

TEST_F(ModelTest, PlayNotifiesSelection) {
    createSong("song.mp3");
    build();
    playback_->play(0);
    track_spy_.expectSelectWith(0);
}

TEST_F(ModelTest, AdvanceMovesToNextSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    track_spy_.expectSelectWith(1);
}

TEST_F(ModelTest, RetreatMovesToPreviousSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(2);
    playback_->retreat();
    track_spy_.expectSelectWith(1);
}

TEST_F(ModelTest, RepeatOneReplays) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    repeat_policy_->advance();
    playback_->play(0);
    playback_->end();
    track_spy_.expectStart();
}

TEST_F(ModelTest, RepeatAllLoops) {
    createSong("a.mp3");
    build();
    repeat_policy_->advance();
    repeat_policy_->advance();
    playback_->play(0);
    playback_->end();
    track_spy_.expectSelectWith(0);
}

TEST_F(ModelTest, InsertValidFile) {
    build();
    library_->insert(prepare("new.mp3"));
    library_spy_.expectChange();
    library_spy_.expectFeedback("Song added successfully!");
}

TEST_F(ModelTest, InsertUnsupportedFile) {
    build();
    library_->insert(prepare("doc.txt"));
    library_spy_.expectFeedback("Unsupported file type.");
}

TEST_F(ModelTest, InsertEmptyPath) {
    build();
    library_->insert("");
    library_spy_.expectFeedback("Unsupported file type.");
}

TEST_F(ModelTest, InsertDuplicateFile) {
    createSong("existing.mp3");
    build();
    library_->insert(prepare("existing.mp3"));
    library_spy_.expectFeedback("This song already exists.");
}

TEST_F(ModelTest, RemoveNotifiesChanged) {
    createSong("song.mp3");
    build();
    library_->remove(0);
    library_spy_.expectChange();
}

TEST_F(ModelTest, RemoveReducesPlaylist) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    library_->remove(0);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(1);
}

TEST_F(ModelTest, SortByNameNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    setlist_->announce();
    library_spy_.expectChange();
}

TEST_F(ModelTest, SortByNumberNotifiesChanged) {
    createSong("(2) B.mp3");
    createSong("(1) A.mp3");
    build();
    DurationSort byDuration;
    setlist_->sort(byDuration);
    setlist_->announce();
    library_spy_.expectChange();
}

TEST_F(ModelTest, SearchFiltersSongs) {
    createSong("Hello.mp3");
    createSong("Goodbye.mp3");
    createSong("Hello World.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("Hello", visitor);
    visitor.expectCount(2);
}

TEST_F(ModelTest, SearchNoResults) {
    createSong("Hello.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("ZZZZ", visitor);
    visitor.expectEmpty();
}

TEST_F(ModelTest, AcceptShowsAllSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(3);
}

TEST_F(ModelTest, EndWithoutAdAdvances) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->end();
    track_spy_.expectSelectWith(1);
}

TEST_F(ModelTest, SkipWithoutAdDoesNothing) {
    createSong("song.mp3");
    build();
    EXPECT_FALSE(playback_->skip());
    ad_spy_.expectNoReveal();
}

TEST_F(ModelTest, InsertIncreasesPlaylistSize) {
    build();
    library_->insert(prepare("new.mp3"));
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(1);
}

TEST_F(ModelTest, SortByNameOrders) {
    createSong("C.mp3");
    createSong("A.mp3");
    createSong("B.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectNameAt(0, "A.mp3");
}

TEST_F(ModelTest, MultipleRemoves) {
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

TEST_F(ModelTest, MultipleInserts) {
    build();
    library_->insert(prepare("a.mp3"));
    library_->insert(prepare("b.mp3"));
    library_spy_.expectChanges(2);
}

TEST_F(ModelTest, ReverseNotifiesChanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    setlist_->reverse();
    setlist_->announce();
    library_spy_.expectChange();
}

TEST_F(ModelTest, ReverseInvertsOrder) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    QuickSort byName;
    setlist_->sort(byName);
    setlist_->reverse();
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectNameAt(0, "c.mp3");
    visitor.expectNameAt(2, "a.mp3");
}

TEST_F(ModelTest, RestoreNotifiesChanged) {
    createSong("a.mp3");
    build();
    QuickSort byName;
    setlist_->sort(byName);
    setlist_->restore();
    setlist_->announce();
    library_spy_.expectChange();
}

TEST_F(ModelTest, SortByDateNotifiesChanged) {
    createSong("a.mp3");
    build();
    DateSort byDate;
    setlist_->sort(byDate);
    setlist_->announce();
    library_spy_.expectChange();
}

TEST_F(ModelTest, SortByDateAcceptsSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    DateSort byDate;
    setlist_->sort(byDate);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(2);
}