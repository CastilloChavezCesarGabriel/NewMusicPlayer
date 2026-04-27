#include "SongTitleTest.h"
#include "../../model/song/SongTitleParser.h"

TEST_F(SongTitleTest, ParseExtractsNameFromNumberedFormat) {
    EXPECT_EQ("First Song.mp3", SongTitleParser::parse("(1) First Song.mp3"));
}

TEST_F(SongTitleTest, ParseReturnsOriginalWhenNoNumber) {
    EXPECT_EQ("Hello.wav", SongTitleParser::parse("Hello.wav"));
}

TEST_F(SongTitleTest, ParseTrimsWhitespace) {
    EXPECT_EQ("Song.mp3", SongTitleParser::parse("  Song.mp3  "));
}

TEST_F(SongTitleTest, ParseHandlesMultiDigitNumbers) {
    EXPECT_EQ("Tenth Song.mp3", SongTitleParser::parse("(10) Tenth Song.mp3"));
}

TEST_F(SongTitleTest, ParseReturnsEmptyForWhitespaceOnly) {
    EXPECT_EQ("", SongTitleParser::parse("   "));
}

TEST_F(SongTitleTest, ParseHandlesEmptyString) {
    EXPECT_EQ("", SongTitleParser::parse(""));
}