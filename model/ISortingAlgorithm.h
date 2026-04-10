#ifndef SORTING_ALGORITHM_H
#define SORTING_ALGORITHM_H

#include "Song.h"
#include "ISongVisitor.h"
#include "IArrangementStrategy.h"
#include <vector>

class ISortingAlgorithm : public IArrangementStrategy, public ISongVisitor {
public:
    ~ISortingAlgorithm() override = default;
    void arrange(std::vector<Song>& songs) override = 0;
};

#endif //SORTING_ALGORITHM_H