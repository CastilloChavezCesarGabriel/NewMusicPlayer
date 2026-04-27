#include "SongVisitorSpy.h"
#include <gtest/gtest.h>
#include <algorithm>

void SongVisitorSpy::visit(const std::string& name, const std::string& path) {
    names_.push_back(name);
    paths_.push_back(path);
}

void SongVisitorSpy::expectName(const std::string& name) const {
    EXPECT_TRUE(std::ranges::find(names_, name) != names_.end())
        << "expected name: " << name;
}

void SongVisitorSpy::expectPath(const std::string& path) const {
    EXPECT_TRUE(std::ranges::find(paths_, path) != paths_.end())
        << "expected path: " << path;
}

void SongVisitorSpy::expectEmpty() const {
    EXPECT_TRUE(names_.empty()) << "expected empty, but got " << names_.size();
}

void SongVisitorSpy::expectNotEmpty() const {
    EXPECT_FALSE(names_.empty()) << "expected not empty";
}

void SongVisitorSpy::expectCount(const int expected) const {
    EXPECT_EQ(static_cast<int>(names_.size()), expected)
        << "expected count: " << expected;
}

void SongVisitorSpy::expectNameAt(const int index, const std::string& name) const {
    ASSERT_GE(index, 0) << "negative index";
    ASSERT_LT(index, static_cast<int>(names_.size())) << "index out of range";
    EXPECT_EQ(names_[index], name) << "expected name at " << index;
}