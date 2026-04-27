#include "TrackListenerSpy.h"
#include <gtest/gtest.h>
#include <algorithm>

void TrackListenerSpy::onStart(const std::string& path) {
    starts_.push_back(path);
}

void TrackListenerSpy::onSelect(const int index) {
    selections_.push_back(index);
}

void TrackListenerSpy::onStop() {
    stops_++;
}

void TrackListenerSpy::expectStart() const {
    EXPECT_FALSE(starts_.empty()) << "expected onStart to have been received";
}

void TrackListenerSpy::expectStartWith(const std::string& path) const {
    EXPECT_TRUE(std::ranges::find(starts_, path) != starts_.end())
        << "expected onStart with path: " << path;
}

void TrackListenerSpy::expectNoStart() const {
    EXPECT_TRUE(starts_.empty()) << "expected no onStart, but got " << starts_.size();
}

void TrackListenerSpy::expectSelect() const {
    EXPECT_FALSE(selections_.empty()) << "expected onSelect to have been received";
}

void TrackListenerSpy::expectSelectWith(const int index) const {
    EXPECT_TRUE(std::ranges::find(selections_, index) != selections_.end())
        << "expected onSelect with index: " << index;
}

void TrackListenerSpy::expectNoSelect() const {
    EXPECT_TRUE(selections_.empty()) << "expected no onSelect, but got " << selections_.size();
}

void TrackListenerSpy::expectNoSelectWith(const int index) const {
    EXPECT_TRUE(std::ranges::find(selections_, index) == selections_.end())
        << "expected no onSelect with index: " << index;
}

void TrackListenerSpy::expectStop() const {
    EXPECT_GT(stops_, 0) << "expected onStop to have been received";
}

void TrackListenerSpy::expectNoStop() const {
    EXPECT_EQ(stops_, 0) << "expected no onStop, but got " << stops_;
}