#ifndef SHELL_SORT_TEST_H
#define SHELL_SORT_TEST_H

#include "../DirectoryTestFixture.h"
#include "../../model/tracklist/DurationSort.h"
#include "../SongVisitorSpy.h"
#include <string>

class ShellSortTest : public DirectoryTestFixture {
protected:
    DurationSort sorter_;
    SongVisitorSpy visitor_;

    std::string identify() const override;
    std::string createSizedFile(const std::string& name, int size) const;
};

#endif //SHELL_SORT_TEST_H