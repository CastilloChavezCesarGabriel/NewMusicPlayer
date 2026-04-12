#include "AddSongUseCaseTest.h"
#include "../../model/tracklist/QuickSort.h"
#include "../TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

std::string AddSongUseCaseTest::identify() const {
    return "add_uc";
}

std::string AddSongUseCaseTest::prepare(const std::string& name) const {
    const std::string src_directory_ = base_directory_ + "/src";
    std::filesystem::create_directories(src_directory_);
    std::string path = src_directory_ + "/" + name;
    std::ofstream(path) << "audio";
    return path;
}

TEST_F(AddSongUseCaseTest, AddValidMp3GivesSuccessFeedback) {
    build();
    std::string path = prepare("song.mp3");
    library_->insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Song added successfully!"));
}

TEST_F(AddSongUseCaseTest, AddValidWavGivesSuccessFeedback) {
    build();
    std::string path = prepare("song.wav");
    library_->insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Song added successfully!"));
}

TEST_F(AddSongUseCaseTest, AddUnsupportedTypeGivesFeedback) {
    build();
    std::string path = prepare("song.txt");
    library_->insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddEmptyPathGivesFeedback) {
    build();
    library_->insert("");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddDuplicateGivesFeedback) {
    createSong("song.mp3");
    build();
    std::string path = prepare("song.mp3");
    library_->insert(path);
    EXPECT_TRUE(listener_.wasFeedback("This song already exists."));
}

TEST_F(AddSongUseCaseTest, AddIncreasesPlaylistSize) {
    build();
    std::string path = prepare("song.mp3");
    library_->insert(path);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddNotifiesChanged) {
    build();
    std::string path = prepare("song.mp3");
    library_->insert(path);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddSongAppearsInPlaylist) {
    build();
    std::string path = prepare("my_track.mp3");
    library_->insert(path);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasName("my_track.mp3"));
}

TEST_F(AddSongUseCaseTest, AddMultipleSongs) {
    build();
    std::string p1 = prepare("a.mp3");
    library_->insert(p1);
    std::string p2 = prepare("b.mp3");
    library_->insert(p2);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(AddSongUseCaseTest, AddMultipleSongsNotifiesMultipleTimes) {
    build();
    std::string p1 = prepare("a.mp3");
    library_->insert(p1);
    std::string p2 = prepare("b.mp3");
    library_->insert(p2);
    EXPECT_TRUE(listener_.wasChangedTimes(2));
}

TEST_F(AddSongUseCaseTest, AddAfterRemove) {
    createSong("existing.mp3");
    build();
    library_->remove(0);
    std::string path = prepare("new.mp3");
    library_->insert(path);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasName("new.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenSort) {
    createSong("c.mp3");
    build();
    std::string path = prepare("a.mp3");
    library_->insert(path);
    QuickSort byTitle;
    setlist_->sort(byTitle);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenSearch) {
    build();
    std::string path = prepare("unique.mp3");
    library_->insert(path);
    TestPlaylistVisitor visitor;
    catalog_->search("unique", visitor);
    EXPECT_TRUE(visitor.hasName("unique.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenPlayNewSong) {
    build();
    std::string path = prepare("song.mp3");
    library_->insert(path);
    playback_->play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(AddSongUseCaseTest, AddDoesNotStartPlayback) {
    build();
    std::string path = prepare("song.mp3");
    library_->insert(path);
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(AddSongUseCaseTest, AddDoesNotSelect) {
    build();
    std::string path = prepare("song.mp3");
    library_->insert(path);
    EXPECT_FALSE(listener_.wasSelected());
}

TEST_F(AddSongUseCaseTest, AddOggGivesFeedback) {
    build();
    std::string path = prepare("song.ogg");
    library_->insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddFlacGivesFeedback) {
    build();
    std::string path = prepare("song.flac");
    library_->insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddUnsupportedDoesNotIncreasePlaylist) {
    build();
    std::string path = prepare("song.txt");
    library_->insert(path);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(AddSongUseCaseTest, AddUnsupportedDoesNotNotifyChanged) {
    build();
    std::string path = prepare("song.txt");
    library_->insert(path);
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddDuplicateDoesNotIncreasePlaylist) {
    createSong("song.mp3");
    build();
    std::string path = prepare("song.mp3");
    library_->insert(path);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddDuplicateDoesNotNotifyChanged) {
    createSong("song.mp3");
    build();
    std::string path = prepare("song.mp3");
    library_->insert(path);
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddToExistingPlaylist) {
    createSong("existing.mp3");
    build();
    std::string path = prepare("new.mp3");
    library_->insert(path);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(AddSongUseCaseTest, AddPreservesExistingSongs) {
    createSong("existing.mp3");
    build();
    std::string path = prepare("new.mp3");
    library_->insert(path);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasName("existing.mp3"));
    EXPECT_TRUE(visitor.hasName("new.mp3"));
}

TEST_F(AddSongUseCaseTest, AddEmptyPathDoesNotIncreasePlaylist) {
    build();
    library_->insert("");
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(AddSongUseCaseTest, AddThreeSongsSequentially) {
    build();
    library_->insert(prepare("a.mp3"));
    library_->insert(prepare("b.mp3"));
    library_->insert(prepare("c.mp3"));
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(AddSongUseCaseTest, AddThenRemoveThenAdd) {
    build();
    library_->insert(prepare("a.mp3"));
    library_->remove(0);
    library_->insert(prepare("b.mp3"));
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
    EXPECT_TRUE(visitor.hasName("b.mp3"));
}

TEST_F(AddSongUseCaseTest, AddWavIncreasesPlaylist) {
    build();
    library_->insert(prepare("track.wav"));
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddThenSortThenSearch) {
    build();
    library_->insert(prepare("zebra.mp3"));
    library_->insert(prepare("alpha.mp3"));
    QuickSort byTitle;
    setlist_->sort(byTitle);
    TestPlaylistVisitor visitor;
    catalog_->search("alpha", visitor);
    EXPECT_TRUE(visitor.hasName("alpha.mp3"));
}

TEST_F(AddSongUseCaseTest, AddDoesNotCrashOnEmptyPlaylist) {
    build();
    std::string path = prepare("song.mp3");
    EXPECT_NO_THROW(library_->insert(path));
}
