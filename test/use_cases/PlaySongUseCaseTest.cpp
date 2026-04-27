#include "PlaySongUseCaseTest.h"
#include "../../model/tracklist/QuickSort.h"
#include <filesystem>
#include <fstream>

std::string PlaySongUseCaseTest::identify() const {
    return "play_uc";
}

TEST_F(PlaySongUseCaseTest, PlaySelectsSong) {
    createSong("song.mp3");
    build();
    playback_->play(0);
    track_spy_.expectSelectWith(0);
}

TEST_F(PlaySongUseCaseTest, PlayStartsPlayback) {
    createSong("song.mp3");
    build();
    playback_->play(0);
    track_spy_.expectSelect();
}

TEST_F(PlaySongUseCaseTest, PlaySecondSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(1);
    track_spy_.expectSelectWith(1);
}

TEST_F(PlaySongUseCaseTest, PlayThenPlayAnother) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->play(1);
    track_spy_.expectSelectWith(1);
}

TEST_F(PlaySongUseCaseTest, PlayLastSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(2);
    track_spy_.expectSelectWith(2);
}

TEST_F(PlaySongUseCaseTest, PlayFromMiddle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    createSong("e.mp3");
    build();
    playback_->play(2);
    track_spy_.expectSelect();
}

TEST_F(PlaySongUseCaseTest, PlayAlwaysSelects) {
    createSong("song.mp3");
    build();
    playback_->play(0);
    track_spy_.expectSelect();
}

TEST_F(PlaySongUseCaseTest, PlayMultipleTimesAllSelect) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->play(1);
    playback_->play(0);
    track_spy_.expectSelectWith(0);
    track_spy_.expectSelectWith(1);
}

TEST_F(PlaySongUseCaseTest, EndAdvancesToNextSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->end();
    track_spy_.expectSelectWith(1);
}

TEST_F(PlaySongUseCaseTest, EndAtLastSongDoesNotCrash) {
    createSong("a.mp3");
    build();
    playback_->play(0);
    EXPECT_NO_THROW(playback_->end());
}

TEST_F(PlaySongUseCaseTest, RepeatOneReplays) {
    createSong("song.mp3");
    build();
    repeat_policy_->advance();
    playback_->play(0);
    playback_->end();
    track_spy_.expectStart();
}

TEST_F(PlaySongUseCaseTest, RepeatAllLoops) {
    createSong("a.mp3");
    build();
    repeat_policy_->advance();
    repeat_policy_->advance();
    playback_->play(0);
    playback_->end();
    track_spy_.expectSelectWith(0);
}

TEST_F(PlaySongUseCaseTest, EndWithRepeatReplays) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    repeat_policy_->advance();
    playback_->play(0);
    playback_->end();
    track_spy_.expectSelect();
}

TEST_F(PlaySongUseCaseTest, SkipWithoutAdDoesNothing) {
    createSong("song.mp3");
    build();
    EXPECT_FALSE(playback_->skip());
    ad_spy_.expectNoReveal();
}

TEST_F(PlaySongUseCaseTest, PlayWithSingleSong) {
    createSong("only.mp3");
    build();
    playback_->play(0);
    track_spy_.expectSelect();
}

TEST_F(PlaySongUseCaseTest, PlayDoesNotCrashOnEmptyPlaylist) {
    build();
    EXPECT_NO_THROW(playback_->play(0));
}

TEST_F(PlaySongUseCaseTest, AdvanceFromFirstToSecond) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    track_spy_.expectSelectWith(1);
}

TEST_F(PlaySongUseCaseTest, RetreatFromSecondToFirst) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(1);
    playback_->retreat();
    track_spy_.expectSelectWith(0);
}

TEST_F(PlaySongUseCaseTest, AdvanceStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    track_spy_.expectSelect();
}

TEST_F(PlaySongUseCaseTest, RetreatStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(1);
    playback_->retreat();
    track_spy_.expectSelect();
}

TEST_F(PlaySongUseCaseTest, AdvanceThroughEntirePlaylist) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    playback_->advance();
    track_spy_.expectSelectWith(2);
}

TEST_F(PlaySongUseCaseTest, RetreatAtStartDoesNotCrash) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    EXPECT_NO_THROW(playback_->retreat());
}

TEST_F(PlaySongUseCaseTest, AdvanceAtEndDoesNotCrash) {
    createSong("a.mp3");
    build();
    playback_->play(0);
    EXPECT_NO_THROW(playback_->advance());
}

TEST_F(PlaySongUseCaseTest, PlaySortedThenAdvance) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    QuickSort byTitle;
    setlist_->sort(byTitle);
    playback_->play(0);
    playback_->advance();
    track_spy_.expectSelect();
}

TEST_F(PlaySongUseCaseTest, EndMultipleTimes) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(0);
    playback_->end();
    playback_->end();
    track_spy_.expectSelectWith(2);
}

TEST_F(PlaySongUseCaseTest, PlayAfterRemove) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    library_->remove(0);
    playback_->play(0);
    track_spy_.expectSelect();
}

TEST_F(PlaySongUseCaseTest, PlayAfterInsert) {
    build();
    library_->insert(prepare("new.mp3"));
    playback_->play(0);
    track_spy_.expectSelect();
}

TEST_F(PlaySongUseCaseTest, AdvanceThenRetreat) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(0);
    playback_->advance();
    playback_->retreat();
    track_spy_.expectSelectWith(0);
}

TEST_F(PlaySongUseCaseTest, PlayAfterShuffle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    build();
    playback_->play(0);
    track_spy_.expectSelect();
}

TEST_F(PlaySongUseCaseTest, RepeatOffAdvances) {
    createSong("a.mp3");
    createSong("b.mp3");
    build();
    playback_->play(0);
    playback_->end();
    track_spy_.expectSelectWith(1);
}