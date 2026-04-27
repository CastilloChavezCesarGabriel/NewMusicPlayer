#include "LibraryListenerSpy.h"
#include <gtest/gtest.h>
#include <algorithm>

void LibraryListenerSpy::onChanged() {
    changes_++;
}

void LibraryListenerSpy::onFeedback(const std::string& message, bool) {
    feedbacks_.push_back(message);
}

void LibraryListenerSpy::expectChange() const {
    EXPECT_GT(changes_, 0) << "expected onChanged to have been received";
}

void LibraryListenerSpy::expectChanges(const int expected) const {
    EXPECT_EQ(changes_, expected) << "expected onChanged count: " << expected;
}

void LibraryListenerSpy::expectNoChange() const {
    EXPECT_EQ(changes_, 0) << "expected no onChanged, but got " << changes_;
}

void LibraryListenerSpy::expectFeedback(const std::string& message) const {
    EXPECT_TRUE(std::ranges::find(feedbacks_, message) != feedbacks_.end())
        << "expected feedback: " << message;
}

void LibraryListenerSpy::expectNoFeedback(const std::string& message) const {
    EXPECT_TRUE(std::ranges::find(feedbacks_, message) == feedbacks_.end())
        << "expected no feedback: " << message;
}