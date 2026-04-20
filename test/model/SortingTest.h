#ifndef SORTINGTEST_H
#define SORTINGTEST_H

#include "../DirectoryTestFixture.h"
#include "../../model/tracklist/DurationSort.h"
#include "../../model/tracklist/QuickSort.h"
#include "../TestPlaylistVisitor.h"
#include <string>

class ShellSortTest : public DirectoryTestFixture {
protected:
    DurationSort sorter_;
    TestPlaylistVisitor visitor_;

    std::string identify() const override;
    std::string createSizedFile(const std::string& name, int size) const;
};

class QuickSortTest : public ::testing::Test {
protected:
    QuickSort sorter_;
    TestPlaylistVisitor visitor_;
};

#endif