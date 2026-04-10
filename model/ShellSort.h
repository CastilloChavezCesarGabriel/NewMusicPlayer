#ifndef SHELL_SORT_H
#define SHELL_SORT_H
#include "ISortingAlgorithm.h"

class ShellSort : public ISortingAlgorithm {
protected:
    long long key_ = 0;

private:
    void sweep(std::vector<Song>& songs, int gap);

public:
    void arrange(std::vector<Song>& songs) override;
};

#endif //SHELL_SORT_H