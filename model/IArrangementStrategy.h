#ifndef I_ARRANGEMENT_STRATEGY_H
#define I_ARRANGEMENT_STRATEGY_H

#include "Song.h"
#include <vector>

class IArrangementStrategy {
public:
    virtual ~IArrangementStrategy() = default;
    virtual void arrange(std::vector<Song>& songs) = 0;
};

#endif //I_ARRANGEMENT_STRATEGY_H
