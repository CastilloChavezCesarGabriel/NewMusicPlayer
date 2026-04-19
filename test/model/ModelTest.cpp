#include "ModelTest.h"
#include "../TestPlaylistVisitor.h"
#include "../../model/tracklist/QuickSort.h"
#include "../../model/tracklist/DurationSort.h"
#include "../../model/tracklist/DateSort.h"
#include <filesystem>
#include <fstream>

std::string ModelTest::identify() const {
    return "model_test";
}

TEST_F(ModelTest, LoadsSongsFromDirectory) {
    createSong("(1) First.mp3");
    createSong("(2) Second.mp3");
    build();
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(ModelTest, LoadsEmptyDirectory) {
    build();
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(ModelTest, PlaySelectsAndStartsSong) {
    createSong("song.mp3");
    build();
    playback_->play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(ModelTest, PlayNotifiesSelection) {
    createSong("song.mp3");
    build();
    playback_->play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(ModelTest, AdvanceMovesToNextSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(ModelTest, RetreatMovesToPreviousSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(2);
    playback_->retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(ModelTest, RepeatOneReplays) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    repeat_mode_->advance();
    playback_->play(0);
    playback_->end();
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(ModelTest, RepeatAllLoops) {
    createSong("a.mp3");
    build();
    repeat_mode_->advance();
    repeat_mode_->advance();
    playback_->play(0);
    playback_->end();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(ModelTest, InsertValidFile) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";

    build();
    library_->insert(srcDir + "/new.mp3");
    EXPECT_TRUE(listener_.wasChanged());
    EXPECT_TRUE(listener_.wasFeedback("Song added successfully!"));
}

TEST_F(ModelTest, InsertUnsupportedFile) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/doc.txt") << "text";

    build();
    library_->insert(srcDir + "/doc.txt");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(ModelTest, InsertEmptyPath) {
    build();
    library_->insert("");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(ModelTest, InsertDuplicateFile) {
    createSong("existing.mp3");
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/existing.mp3") << "audio";

    build();
    library_->insert(srcDir + "/existing.mp3");
    EXPECT_TRUE(listener_.wasFeedback("This song already exists."));
}

TEST_F(ModelTest, RemoveNotifiesChanged) {
    createSong("song.mp3");
    build();
    library_->remove(0);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, RemoveReducesPlaylist) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    library_->remove(0);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, SortByNameNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SortByNumberNotifiesChanged) {
    createSong("(2) B.mp3");
    createSong("(1) A.mp3");
    build();
    DurationSort byDuration;
    setlist_->sort(byDuration);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SearchFiltersSongs) {
    createSong("Hello.mp3");
    createSong("Goodbye.mp3");
    createSong("Hello World.mp3");
    build();
    TestPlaylistVisitor visitor;
    catalog_->search("Hello", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(ModelTest, SearchNoResults) {
    createSong("Hello.mp3");
    build();
    TestPlaylistVisitor visitor;
    catalog_->search("ZZZZ", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(ModelTest, AcceptShowsAllSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(ModelTest, EndWithoutAdAdvances) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->end();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(ModelTest, SkipWithoutAdDoesNothing) {
    createSong("song.mp3");
    build();
    playback_->skip();
    EXPECT_FALSE(listener_.wasRevealed());
}

TEST_F(ModelTest, InsertIncreasesPlaylistSize) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";

    build();
    library_->insert(srcDir + "/new.mp3");
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, SortByNameOrders) {
    createSong("C.mp3");
    createSong("A.mp3");
    createSong("B.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
}

TEST_F(ModelTest, MultipleRemoves) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    library_->remove(0);
    library_->remove(0);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, MultipleInserts) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/a.mp3") << "audio";
    std::ofstream(srcDir + "/b.mp3") << "audio";

    build();
    library_->insert(srcDir + "/a.mp3");
    library_->insert(srcDir + "/b.mp3");
    EXPECT_TRUE(listener_.wasChangedTimes(2));
}

TEST_F(ModelTest, ReverseNotifiesChanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    setlist_->reverse();
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, ReverseInvertsOrder) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    QuickSort byName;
    setlist_->sort(byName);
    setlist_->reverse();
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "c.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "a.mp3"));
}

TEST_F(ModelTest, RestoreNotifiesChanged) {
    createSong("a.mp3");
    build();
    QuickSort byName;
    setlist_->sort(byName);
    setlist_->restore();
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SortByDateNotifiesChanged) {
    createSong("a.mp3");
    build();
    DateSort byDate;
    setlist_->sort(byDate);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SortByDateAcceptsSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    DateSort byDate;
    setlist_->sort(byDate);
    TestPlaylistVisitor visitor;
    catalog_->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}
