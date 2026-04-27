#include "AdSchedulerTest.h"

void AdSchedulerTest::SetUp() {
    DirectoryTestFixture::SetUp();
    track_bus_.add(track_spy_);
}

std::string AdSchedulerTest::identify() const {
    return "ad_test";
}

bool AdSchedulerTest::interruptsAtLeastOnce(AdScheduler& ad) {
    for (int i = 0; i < 100; i++) {
        if (ad.interrupt()) {
            ad.conclude();
            return true;
        }
    }
    return false;
}

TEST_F(AdSchedulerTest, LoadFindsAudioFiles) {
    createFile("ad1.mp3");
    createFile("ad2.wav");
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    EXPECT_TRUE(interruptsAtLeastOnce(ad));
}

TEST_F(AdSchedulerTest, LoadIgnoresNonAudioFiles) {
    createFile("readme.txt");
    createFile("image.png");
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    EXPECT_FALSE(ad.interrupt());
}

TEST_F(AdSchedulerTest, LoadEmptyDirectory) {
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    EXPECT_FALSE(ad.interrupt());
}

TEST_F(AdSchedulerTest, LoadNonExistentDirectory) {
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load("/nonexistent/path");
    EXPECT_FALSE(ad.interrupt());
}

TEST_F(AdSchedulerTest, InterruptStartsPlayback) {
    createFile("ad.mp3");
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    while (!ad.interrupt()) {}
    track_spy_.expectStart();
}

TEST_F(AdSchedulerTest, InterruptReturnsTrueWithAds) {
    createFile("ad.mp3");
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    EXPECT_TRUE(interruptsAtLeastOnce(ad));
}

TEST_F(AdSchedulerTest, InterruptReturnsFalseWhenNoAds) {
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    EXPECT_FALSE(ad.interrupt());
}

TEST_F(AdSchedulerTest, ConcludeReturnsTrueAfterInterrupt) {
    createFile("ad.mp3");
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    while (!ad.interrupt()) {}
    EXPECT_TRUE(ad.conclude());
}

TEST_F(AdSchedulerTest, ConcludeReturnsFalseWithoutInterrupt) {
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    EXPECT_FALSE(ad.conclude());
}

TEST_F(AdSchedulerTest, ConcludeReturnsFalseOnSecondCall) {
    createFile("ad.mp3");
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    while (!ad.interrupt()) {}
    ad.conclude();
    EXPECT_FALSE(ad.conclude());
}

TEST_F(AdSchedulerTest, InterruptAfterConcludeWorks) {
    createFile("ad.mp3");
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    while (!ad.interrupt()) {}
    ad.conclude();
    while (!ad.interrupt()) {}
    EXPECT_TRUE(ad.conclude());
}

TEST_F(AdSchedulerTest, LoadMixedFiles) {
    createFile("ad1.mp3");
    createFile("readme.txt");
    createFile("ad2.wav");
    createFile("image.jpg");
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    EXPECT_TRUE(interruptsAtLeastOnce(ad));
}

TEST_F(AdSchedulerTest, InterruptPlaysFromLoadedAds) {
    createFile("only_ad.mp3");
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    while (!ad.interrupt()) {}
    track_spy_.expectStart();
}

TEST_F(AdSchedulerTest, MultipleInterruptsAllStart) {
    createFile("ad.mp3");
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    while (!ad.interrupt()) {}
    ad.conclude();
    while (!ad.interrupt()) {}
    track_spy_.expectStart();
}

TEST_F(AdSchedulerTest, ConcludeWithoutLoadReturnsFalse) {
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    EXPECT_FALSE(ad.conclude());
}

TEST_F(AdSchedulerTest, LoadMultipleMp3Files) {
    for (int i = 0; i < 8; i++) {
        createFile("ad" + std::to_string(i) + ".mp3");
    }
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    EXPECT_TRUE(interruptsAtLeastOnce(ad));
}

TEST_F(AdSchedulerTest, InterruptDoesNotStartWhenEmpty) {
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    ad.interrupt();
    track_spy_.expectNoStart();
}

TEST_F(AdSchedulerTest, LoadWavFiles) {
    createFile("sound.wav");
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    EXPECT_TRUE(interruptsAtLeastOnce(ad));
}

TEST_F(AdSchedulerTest, InterruptProducesVariation) {
    createFile("ad.mp3");
    AdScheduler ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    int trueCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (ad.interrupt()) {
            trueCount++;
            ad.conclude();
        }
    }
    EXPECT_GT(trueCount, 0);
    EXPECT_LT(trueCount, 1000);
}