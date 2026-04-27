#include "ShellSortTest.h"
#include <fstream>

std::string ShellSortTest::identify() const {
    return "shell_sort_test";
}

std::string ShellSortTest::createSizedFile(const std::string& name, const int size) const {
    const std::string path = test_directory_ + "/" + name;
    std::ofstream(path) << std::string(size, 'x');
    return path;
}

TEST_F(ShellSortTest, SortByDurationAscending) {
    const std::string longTrack = createSizedFile("c.mp3", 300);
    const std::string shortTrack = createSizedFile("a.mp3", 100);
    const std::string mediumTrack = createSizedFile("b.mp3", 200);

    std::vector<Song> songs = {
        Song("c.mp3", longTrack),
        Song("a.mp3", shortTrack),
        Song("b.mp3", mediumTrack)
    };

    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "a.mp3");
}

TEST_F(ShellSortTest, SortAlreadySorted) {
    const std::string shortTrack = createSizedFile("a.mp3", 100);
    const std::string mediumTrack = createSizedFile("b.mp3", 200);
    const std::string longTrack = createSizedFile("c.mp3", 300);

    std::vector<Song> songs = {
        Song("a.mp3", shortTrack),
        Song("b.mp3", mediumTrack),
        Song("c.mp3", longTrack)
    };

    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "a.mp3");
}

TEST_F(ShellSortTest, SortReversed) {
    const std::string veryLongTrack = createSizedFile("e.mp3", 500);
    const std::string longTrack = createSizedFile("d.mp3", 400);
    const std::string mediumTrack = createSizedFile("c.mp3", 300);
    const std::string shortTrack = createSizedFile("b.mp3", 200);
    const std::string veryShortTrack = createSizedFile("a.mp3", 100);

    std::vector<Song> songs = {
        Song("e.mp3", veryLongTrack),
        Song("d.mp3", longTrack),
        Song("c.mp3", mediumTrack),
        Song("b.mp3", shortTrack),
        Song("a.mp3", veryShortTrack)
    };

    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "a.mp3");
}

TEST_F(ShellSortTest, SortSingleElement) {
    const std::string track = createSizedFile("a.mp3", 100);
    std::vector<Song> songs = {Song("a.mp3", track)};
    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "a.mp3");
}

TEST_F(ShellSortTest, SortEmptyVector) {
    std::vector<Song> songs;
    sorter_.arrange(songs);
    EXPECT_TRUE(songs.empty());
}

TEST_F(ShellSortTest, SortDuplicateSizes) {
    const std::string firstMediumTrack = createSizedFile("b.mp3", 200);
    const std::string shortTrack = createSizedFile("a.mp3", 100);
    const std::string secondMediumTrack = createSizedFile("c.mp3", 200);

    std::vector<Song> songs = {
        Song("b.mp3", firstMediumTrack),
        Song("a.mp3", shortTrack),
        Song("c.mp3", secondMediumTrack)
    };

    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "a.mp3");
}

TEST_F(ShellSortTest, SortPreservesAllElements) {
    const std::string longTrack = createSizedFile("c.mp3", 300);
    const std::string shortTrack = createSizedFile("a.mp3", 100);
    const std::string mediumTrack = createSizedFile("b.mp3", 200);

    std::vector<Song> songs = {
        Song("c.mp3", longTrack),
        Song("a.mp3", shortTrack),
        Song("b.mp3", mediumTrack)
    };

    sorter_.arrange(songs);
    EXPECT_EQ(3, songs.size());
}

TEST_F(ShellSortTest, SortTwoElements) {
    const std::string mediumTrack = createSizedFile("b.mp3", 200);
    const std::string shortTrack = createSizedFile("a.mp3", 100);

    std::vector<Song> songs = {
        Song("b.mp3", mediumTrack),
        Song("a.mp3", shortTrack)
    };

    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "a.mp3");
}

TEST_F(ShellSortTest, SortLargeCollection) {
    std::vector<Song> songs;
    for (int i = 100; i > 0; i--) {
        const std::string name = std::to_string(i) + ".mp3";
        const std::string path = createSizedFile(name, i * 10);
        songs.emplace_back(name, path);
    }
    sorter_.arrange(songs);
    songs[0].accept(visitor_);
    visitor_.expectNameAt(0, "1.mp3");
}