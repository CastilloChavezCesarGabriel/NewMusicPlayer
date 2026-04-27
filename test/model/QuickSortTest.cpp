#include "QuickSortTest.h"

TEST_F(QuickSortTest, SortByNameAlphabetical) {
    std::vector<Song> songs = {
        Song("C.mp3", "/c"),
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b")
    };
    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "A.mp3");
}

TEST_F(QuickSortTest, SortAlreadySorted) {
    std::vector<Song> songs = {
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b"),
        Song("C.mp3", "/c")
    };
    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "A.mp3");
}

TEST_F(QuickSortTest, SortReversed) {
    std::vector<Song> songs = {
        Song("E.mp3", "/e"),
        Song("D.mp3", "/d"),
        Song("C.mp3", "/c"),
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "A.mp3");
}

TEST_F(QuickSortTest, SortSingleElement) {
    std::vector<Song> songs = { Song("A.mp3", "/a") };
    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "A.mp3");
}

TEST_F(QuickSortTest, SortEmptyVector) {
    std::vector<Song> songs;
    sorter_.arrange(songs);
    EXPECT_TRUE(songs.empty());
}

TEST_F(QuickSortTest, SortDuplicateNames) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b2")
    };
    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "A.mp3");
}

TEST_F(QuickSortTest, SortLargeCollection) {
    std::vector<Song> songs;
    for (int i = 100; i > 0; i--) {
        songs.emplace_back(std::to_string(i) + ".mp3", "/s");
    }
    sorter_.arrange(songs);
    EXPECT_EQ(100, songs.size());
}

TEST_F(QuickSortTest, SortPreservesAllElements) {
    std::vector<Song> songs = {
        Song("C.mp3", "/c"),
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b")
    };
    sorter_.arrange(songs);
    EXPECT_EQ(3, songs.size());
}

TEST_F(QuickSortTest, SortTwoElements) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "A.mp3");
}

TEST_F(QuickSortTest, SortNumberedSongsByTitle) {
    std::vector<Song> songs = {
        Song("(2) Banana.mp3", "/b"),
        Song("(1) Cherry.mp3", "/c"),
        Song("(3) Apple.mp3", "/a")
    };
    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "(3) Apple.mp3");
}