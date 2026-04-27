#ifndef SONGTEST_H
#define SONGTEST_H

#include <gtest/gtest.h>
#include "../SongVisitorSpy.h"

class SongTest : public::testing::Test {
protected:
    SongVisitorSpy visitor_;
};

#endif