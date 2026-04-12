#include "AdvertisementTest.h"
#include "../../model/playback/Advertisement.h"
#include <fstream>

void AdvertisementTest::SetUp() {
    DirectoryTestFixture::SetUp();
    ad_bus_.add(listener_);
    track_bus_.add(listener_);
}

std::string AdvertisementTest::identify() const {
    return "ad_test";
}

TEST_F(AdvertisementTest, LoadFindsAudioFiles) {
    createFile("ad1.mp3");
    createFile("ad2.wav");
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt();
        if (interrupted) ad.conclude();
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, LoadIgnoresNonAudioFiles) {
    createFile("readme.txt");
    createFile("image.png");
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    EXPECT_FALSE(ad.interrupt());
}

TEST_F(AdvertisementTest, LoadEmptyDirectory) {
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    EXPECT_FALSE(ad.interrupt());
}

TEST_F(AdvertisementTest, LoadNonExistentDirectory) {
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load("/nonexistent/path");
    EXPECT_FALSE(ad.interrupt());
}

TEST_F(AdvertisementTest, InterruptStartsPlayback) {
    createFile("ad.mp3");
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    while (!ad.interrupt()) {}
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(AdvertisementTest, InterruptReturnsTrueWithAds) {
    createFile("ad.mp3");
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt();
        if (interrupted) ad.conclude();
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, InterruptReturnsFalseWhenNoAds) {
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    EXPECT_FALSE(ad.interrupt());
}

TEST_F(AdvertisementTest, ConcludeReturnsTrueAfterInterrupt) {
    createFile("ad.mp3");
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    while (!ad.interrupt()) {}
    EXPECT_TRUE(ad.conclude());
}

TEST_F(AdvertisementTest, ConcludeReturnsFalseWithoutInterrupt) {
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    EXPECT_FALSE(ad.conclude());
}

TEST_F(AdvertisementTest, ConcludeReturnsFalseOnSecondCall) {
    createFile("ad.mp3");
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    while (!ad.interrupt()) {}
    ad.conclude();
    EXPECT_FALSE(ad.conclude());
}

TEST_F(AdvertisementTest, InterruptAfterConcludeWorks) {
    createFile("ad.mp3");
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    while (!ad.interrupt()) {}
    ad.conclude();
    while (!ad.interrupt()) {}
    EXPECT_TRUE(ad.conclude());
}

TEST_F(AdvertisementTest, LoadMixedFiles) {
    createFile("ad1.mp3");
    createFile("readme.txt");
    createFile("ad2.wav");
    createFile("image.jpg");
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt();
        if (interrupted) ad.conclude();
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, InterruptPlaysFromLoadedAds) {
    createFile("only_ad.mp3");
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    while (!ad.interrupt()) {}
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(AdvertisementTest, MultipleInterruptsAllStart) {
    createFile("ad.mp3");
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    while (!ad.interrupt()) {}
    ad.conclude();
    while (!ad.interrupt()) {}
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(AdvertisementTest, ConcludeWithoutLoadReturnsFalse) {
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    EXPECT_FALSE(ad.conclude());
}

TEST_F(AdvertisementTest, LoadMultipleMp3Files) {
    for (int i = 0; i < 8; i++) {
        createFile("ad" + std::to_string(i) + ".mp3");
    }
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt();
        if (interrupted) ad.conclude();
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, InterruptDoesNotStartWhenEmpty) {
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    ad.interrupt();
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(AdvertisementTest, LoadWavFiles) {
    createFile("sound.wav");
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
    ad.load(test_directory_);
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt();
        if (interrupted) ad.conclude();
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, InterruptProducesVariation) {
    createFile("ad.mp3");
    Advertisement ad(ad_policy_, ad_bus_, track_bus_);
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
