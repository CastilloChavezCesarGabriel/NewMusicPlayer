#include "SongTest.h"
#include "../../model/song/Song.h"

TEST_F(SongTest, AcceptPassesNameToVisitor) {
    const Song song("(1) First Song.mp3", "/music/(1) First Song.mp3");
    song.accept(visitor_);
    visitor_.expectName("(1) First Song.mp3");
}

TEST_F(SongTest, AcceptPassesPathToVisitor) {
    const Song song("song.mp3", "/music/song.mp3");
    song.accept(visitor_);
    visitor_.expectPath("/music/song.mp3");
}

TEST_F(SongTest, MatchFindsSubstring) {
    const Song song("Beautiful Now.mp3", "/music/Beautiful Now.mp3");
    EXPECT_TRUE(song.matches("Beautiful"));
}

TEST_F(SongTest, MatchFindsExactName) {
    const Song song("Hello.wav", "/music/Hello.wav");
    EXPECT_TRUE(song.matches("Hello.wav"));
}

TEST_F(SongTest, MatchReturnsFalseForMismatch) {
    const Song song("Hello.wav", "/music/Hello.wav");
    EXPECT_FALSE(song.matches("Goodbye"));
}

TEST_F(SongTest, MatchIsCaseSensitive) {
    const Song song("Hello.wav", "/music/Hello.wav");
    EXPECT_FALSE(song.matches("hello"));
}

TEST_F(SongTest, MatchFindsPartialName) {
    const Song song("Counting Stars.mp3", "/music/Counting Stars.mp3");
    EXPECT_TRUE(song.matches("Stars"));
}

TEST_F(SongTest, MatchEmptyQueryMatchesAll) {
    const Song song("anything.mp3", "/music/anything.mp3");
    EXPECT_TRUE(song.matches(""));
}

TEST_F(SongTest, AcceptMultipleSongsToSameVisitor) {
    const Song firstTrack("A.mp3", "/a");
    const Song secondTrack("B.mp3", "/b");
    firstTrack.accept(visitor_);
    secondTrack.accept(visitor_);
    visitor_.expectCount(2);
}

TEST_F(SongTest, AcceptPreservesOrderInVisitor) {
    const Song firstTrack("A.mp3", "/a");
    const Song secondTrack("B.mp3", "/b");
    firstTrack.accept(visitor_);
    secondTrack.accept(visitor_);
    visitor_.expectNameAt(0, "A.mp3");
    visitor_.expectNameAt(1, "B.mp3");
}

TEST_F(SongTest, MatchWithSpecialCharacters) {
    const Song song("I'm good (Blue).mp3", "/music/I'm good (Blue).mp3");
    EXPECT_TRUE(song.matches("(Blue)"));
}

TEST_F(SongTest, ConstructionWithEmptyName) {
    const Song song("", "/music/empty");
    song.accept(visitor_);
    visitor_.expectName("");
}

TEST_F(SongTest, ConstructionWithEmptyPath) {
    const Song song("song.mp3", "");
    song.accept(visitor_);
    visitor_.expectPath("");
}