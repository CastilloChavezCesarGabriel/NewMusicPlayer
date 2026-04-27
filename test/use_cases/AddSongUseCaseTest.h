#ifndef ADD_SONG_USE_CASE_TEST_H
#define ADD_SONG_USE_CASE_TEST_H

#include "../ModelTestFixture.h"

class AddSongUseCaseTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif //ADD_SONG_USE_CASE_TEST_H