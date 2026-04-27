#ifndef QUICK_SORT_TEST_H
#define QUICK_SORT_TEST_H

#include <gtest/gtest.h>
#include "../../model/tracklist/QuickSort.h"
#include "../SongVisitorSpy.h"

class QuickSortTest : public::testing::Test {
protected:
    QuickSort sorter_;
    SongVisitorSpy visitor_;
};

#endif //QUICK_SORT_TEST_H