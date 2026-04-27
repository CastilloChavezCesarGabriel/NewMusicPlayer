#include "AddSongUseCaseTest.h"
#include "../../model/tracklist/QuickSort.h"
#include "../SongVisitorSpy.h"

std::string AddSongUseCaseTest::identify() const {
    return "add_uc";
}

TEST_F(AddSongUseCaseTest, AddValidMp3GivesSuccessFeedback) {
    build();
    const std::string path = prepare("song.mp3");
    library_->insert(path);
    library_spy_.expectFeedback("Song added successfully!");
}

TEST_F(AddSongUseCaseTest, AddValidWavGivesSuccessFeedback) {
    build();
    const std::string path = prepare("song.wav");
    library_->insert(path);
    library_spy_.expectFeedback("Song added successfully!");
}

TEST_F(AddSongUseCaseTest, AddUnsupportedTypeGivesFeedback) {
    build();
    const std::string path = prepare("song.txt");
    library_->insert(path);
    library_spy_.expectFeedback("Unsupported file type.");
}

TEST_F(AddSongUseCaseTest, AddEmptyPathGivesFeedback) {
    build();
    library_->insert("");
    library_spy_.expectFeedback("Unsupported file type.");
}

TEST_F(AddSongUseCaseTest, AddDuplicateGivesFeedback) {
    createSong("song.mp3");
    build();
    const std::string path = prepare("song.mp3");
    library_->insert(path);
    library_spy_.expectFeedback("This song already exists.");
}

TEST_F(AddSongUseCaseTest, AddIncreasesPlaylistSize) {
    build();
    const std::string path = prepare("song.mp3");
    library_->insert(path);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(1);
}

TEST_F(AddSongUseCaseTest, AddNotifiesChanged) {
    build();
    const std::string path = prepare("song.mp3");
    library_->insert(path);
    library_spy_.expectChange();
}

TEST_F(AddSongUseCaseTest, AddSongAppearsInPlaylist) {
    build();
    const std::string path = prepare("my_track.mp3");
    library_->insert(path);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectName("my_track.mp3");
}

TEST_F(AddSongUseCaseTest, AddMultipleSongs) {
    build();
    const std::string firstSongPath = prepare("a.mp3");
    library_->insert(firstSongPath);
    const std::string secondSongPath = prepare("b.mp3");
    library_->insert(secondSongPath);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(2);
}

TEST_F(AddSongUseCaseTest, AddMultipleSongsNotifiesMultipleTimes) {
    build();
    const std::string firstSongPath = prepare("a.mp3");
    library_->insert(firstSongPath);
    const std::string secondSongPath = prepare("b.mp3");
    library_->insert(secondSongPath);
    library_spy_.expectChanges(2);
}

TEST_F(AddSongUseCaseTest, AddAfterRemove) {
    createSong("existing.mp3");
    build();
    library_->remove(0);
    const std::string path = prepare("new.mp3");
    library_->insert(path);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectName("new.mp3");
}

TEST_F(AddSongUseCaseTest, AddThenSort) {
    createSong("c.mp3");
    build();
    const std::string path = prepare("a.mp3");
    library_->insert(path);
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectNameAt(0, "a.mp3");
}

TEST_F(AddSongUseCaseTest, AddThenSearch) {
    build();
    const std::string path = prepare("unique.mp3");
    library_->insert(path);
    SongVisitorSpy visitor;
    catalog_->search("unique", visitor);
    visitor.expectName("unique.mp3");
}

TEST_F(AddSongUseCaseTest, AddThenPlayNewSong) {
    build();
    const std::string path = prepare("song.mp3");
    library_->insert(path);
    playback_->play(0);
    track_spy_.expectSelect();
}

TEST_F(AddSongUseCaseTest, AddDoesNotStartPlayback) {
    build();
    const std::string path = prepare("song.mp3");
    library_->insert(path);
    track_spy_.expectNoStart();
}

TEST_F(AddSongUseCaseTest, AddDoesNotSelect) {
    build();
    const std::string path = prepare("song.mp3");
    library_->insert(path);
    track_spy_.expectNoSelect();
}

TEST_F(AddSongUseCaseTest, AddOggGivesFeedback) {
    build();
    const std::string path = prepare("song.ogg");
    library_->insert(path);
    library_spy_.expectFeedback("Unsupported file type.");
}

TEST_F(AddSongUseCaseTest, AddFlacGivesFeedback) {
    build();
    const std::string path = prepare("song.flac");
    library_->insert(path);
    library_spy_.expectFeedback("Unsupported file type.");
}

TEST_F(AddSongUseCaseTest, AddUnsupportedDoesNotIncreasePlaylist) {
    build();
    const std::string path = prepare("song.txt");
    library_->insert(path);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectEmpty();
}

TEST_F(AddSongUseCaseTest, AddUnsupportedDoesNotNotifyChanged) {
    build();
    const std::string path = prepare("song.txt");
    library_->insert(path);
    library_spy_.expectNoChange();
}

TEST_F(AddSongUseCaseTest, AddDuplicateDoesNotIncreasePlaylist) {
    createSong("song.mp3");
    build();
    const std::string path = prepare("song.mp3");
    library_->insert(path);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(1);
}

TEST_F(AddSongUseCaseTest, AddDuplicateDoesNotNotifyChanged) {
    createSong("song.mp3");
    build();
    const std::string path = prepare("song.mp3");
    library_->insert(path);
    library_spy_.expectNoChange();
}

TEST_F(AddSongUseCaseTest, AddToExistingPlaylist) {
    createSong("existing.mp3");
    build();
    const std::string path = prepare("new.mp3");
    library_->insert(path);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(2);
}

TEST_F(AddSongUseCaseTest, AddPreservesExistingSongs) {
    createSong("existing.mp3");
    build();
    const std::string path = prepare("new.mp3");
    library_->insert(path);
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectName("existing.mp3");
    visitor.expectName("new.mp3");
}

TEST_F(AddSongUseCaseTest, AddEmptyPathDoesNotIncreasePlaylist) {
    build();
    library_->insert("");
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectEmpty();
}

TEST_F(AddSongUseCaseTest, AddThreeSongsSequentially) {
    build();
    library_->insert(prepare("a.mp3"));
    library_->insert(prepare("b.mp3"));
    library_->insert(prepare("c.mp3"));
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(3);
}

TEST_F(AddSongUseCaseTest, AddThenRemoveThenAdd) {
    build();
    library_->insert(prepare("a.mp3"));
    library_->remove(0);
    library_->insert(prepare("b.mp3"));
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(1);
    visitor.expectName("b.mp3");
}

TEST_F(AddSongUseCaseTest, AddWavIncreasesPlaylist) {
    build();
    library_->insert(prepare("track.wav"));
    SongVisitorSpy visitor;
    catalog_->accept(visitor);
    visitor.expectCount(1);
}

TEST_F(AddSongUseCaseTest, AddThenSortThenSearch) {
    build();
    library_->insert(prepare("zebra.mp3"));
    library_->insert(prepare("alpha.mp3"));
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->search("alpha", visitor);
    visitor.expectName("alpha.mp3");
}

TEST_F(AddSongUseCaseTest, AddDoesNotCrashOnEmptyPlaylist) {
    build();
    const std::string path = prepare("song.mp3");
    EXPECT_NO_THROW(library_->insert(path));
}