#include "PathVisitorSpy.h"
#include <gtest/gtest.h>
#include <algorithm>

void PathVisitorSpy::visit(const std::string& path) {
    paths_.push_back(path);
}

void PathVisitorSpy::expectPath(const std::string& path) const {
    EXPECT_TRUE(std::ranges::find(paths_, path) != paths_.end())
        << "expected path: " << path;
}