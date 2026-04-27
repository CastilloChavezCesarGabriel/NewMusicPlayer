#include "SearchSongUseCaseTest.h"
#include "../SongVisitorSpy.h"
#include "../../model/tracklist/QuickSort.h"
#include <filesystem>
#include <fstream>

std::string SearchSongUseCaseTest::identify() const {
    return "search_uc";
}

TEST_F(SearchSongUseCaseTest, SearchFindsExactMatch) {
    createSong("hello.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("hello", visitor);
    visitor.expectName("hello.mp3");
}

TEST_F(SearchSongUseCaseTest, SearchNoMatchReturnsEmpty) {
    createSong("hello.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("goodbye", visitor);
    visitor.expectEmpty();
}

TEST_F(SearchSongUseCaseTest, SearchEmptyQueryReturnsAll) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("", visitor);
    visitor.expectCount(2);
}

TEST_F(SearchSongUseCaseTest, SearchPartialName) {
    createSong("summer_breeze.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("summer", visitor);
    visitor.expectName("summer_breeze.mp3");
}

TEST_F(SearchSongUseCaseTest, SearchMultipleResults) {
    createSong("rock_anthem.mp3");
    createSong("rock_ballad.mp3");
    createSong("jazz_tune.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("rock", visitor);
    visitor.expectCount(2);
}

TEST_F(SearchSongUseCaseTest, SearchSingleResult) {
    createSong("rock_anthem.mp3");
    createSong("jazz_tune.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("jazz", visitor);
    visitor.expectCount(1);
}

TEST_F(SearchSongUseCaseTest, SearchOnEmptyPlaylist) {
    build();
    SongVisitorSpy visitor;
    catalog_->search("anything", visitor);
    visitor.expectEmpty();
}

TEST_F(SearchSongUseCaseTest, SearchEmptyQueryOnEmptyPlaylist) {
    build();
    SongVisitorSpy visitor;
    catalog_->search("", visitor);
    visitor.expectEmpty();
}

TEST_F(SearchSongUseCaseTest, SearchAfterSort) {
    createSong("cherry.mp3");
    createSong("apple.mp3");
    createSong("banana.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->search("banana", visitor);
    visitor.expectName("banana.mp3");
}

TEST_F(SearchSongUseCaseTest, SearchAfterInsert) {
    createSong("a.mp3");
    build();
    library_->insert(prepare("b.mp3"));
    SongVisitorSpy visitor;
    catalog_->search("b", visitor);
    visitor.expectName("b.mp3");
}

TEST_F(SearchSongUseCaseTest, SearchAfterRemove) {
    createSong("unique_song.mp3");
    build();
    library_->remove(0);
    SongVisitorSpy visitor;
    catalog_->search("unique_song", visitor);
    visitor.expectEmpty();
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotStartPlayback) {
    createSong("song.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("song", visitor);
    track_spy_.expectNoStart();
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotSelect) {
    createSong("song.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("song", visitor);
    track_spy_.expectNoSelect();
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotNotifyChanged) {
    createSong("song.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("song", visitor);
    library_spy_.expectNoChange();
}

TEST_F(SearchSongUseCaseTest, SearchWithExtension) {
    createSong("song.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search(".mp3", visitor);
    visitor.expectName("song.mp3");
}

TEST_F(SearchSongUseCaseTest, SearchWavFile) {
    createSong("track.wav");
    build();
    SongVisitorSpy visitor;
    catalog_->search("track", visitor);
    visitor.expectName("track.wav");
}

TEST_F(SearchSongUseCaseTest, SearchWithUnderscore) {
    createSong("my_song.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("my_song", visitor);
    visitor.expectName("my_song.mp3");
}

TEST_F(SearchSongUseCaseTest, SearchWithDash) {
    createSong("my-song.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("my-song", visitor);
    visitor.expectName("my-song.mp3");
}

TEST_F(SearchSongUseCaseTest, SearchWithNumbers) {
    createSong("track01.mp3");
    createSong("track02.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("track0", visitor);
    visitor.expectCount(2);
}

TEST_F(SearchSongUseCaseTest, SearchSingleCharacter) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("a", visitor);
    visitor.expectName("a.mp3");
}

TEST_F(SearchSongUseCaseTest, SearchTwiceWithDifferentQueries) {
    createSong("rock.mp3");
    createSong("jazz.mp3");
    build();
    SongVisitorSpy v1;
    catalog_->search("rock", v1);
    v1.expectName("rock.mp3");
    SongVisitorSpy v2;
    catalog_->search("jazz", v2);
    v2.expectName("jazz.mp3");
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotAffectPlaylist) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    SongVisitorSpy searchVisitor;
    catalog_->search("a", searchVisitor);
    SongVisitorSpy acceptVisitor;
    catalog_->accept(acceptVisitor);
    acceptVisitor.expectCount(2);
}

TEST_F(SearchSongUseCaseTest, SearchResultHasCorrectName) {
    createSong("specific_name.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("specific", visitor);
    visitor.expectName("specific_name.mp3");
    visitor.expectCount(1);
}

TEST_F(SearchSongUseCaseTest, SearchAllSongsMatch) {
    createSong("song_a.mp3");
    createSong("song_b.mp3");
    createSong("song_c.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("song", visitor);
    visitor.expectCount(3);
}

TEST_F(SearchSongUseCaseTest, SearchNoSongsMatch) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("zzz", visitor);
    visitor.expectEmpty();
}

TEST_F(SearchSongUseCaseTest, SearchAfterSortFindsAll) {
    createSong("rock_a.mp3");
    createSong("rock_b.mp3");
    createSong("jazz.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    SongVisitorSpy visitor;
    catalog_->search("rock", visitor);
    visitor.expectCount(2);
}

TEST_F(SearchSongUseCaseTest, SearchLongQuery) {
    createSong("very_long_song_name_here.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("very_long_song_name_here", visitor);
    visitor.expectName("very_long_song_name_here.mp3");
}

TEST_F(SearchSongUseCaseTest, SearchSingleSongPlaylist) {
    createSong("only.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("only", visitor);
    visitor.expectCount(1);
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotCrashOnEmptyPlaylist) {
    build();
    SongVisitorSpy visitor;
    EXPECT_NO_THROW(catalog_->search("test", visitor));
}

TEST_F(SearchSongUseCaseTest, SearchVisitorIsIndependent) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    SongVisitorSpy v1;
    catalog_->search("a", v1);
    SongVisitorSpy v2;
    catalog_->search("b", v2);
    v1.expectCount(1);
    v2.expectCount(1);
}

TEST_F(SearchSongUseCaseTest, SearchIgnoresCase) {
    createSong("Hello.mp3");
    build();
    SongVisitorSpy visitor;
    catalog_->search("HELLO", visitor);
    visitor.expectName("Hello.mp3");
}