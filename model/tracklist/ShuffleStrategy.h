#ifndef SHUFFLE_STRATEGY_H
#define SHUFFLE_STRATEGY_H

#include "IArrangementStrategy.h"

class ShuffleStrategy final : public IArrangementStrategy {
public:
    void arrange(std::vector<Song>& songs) override;
};

#endif //SHUFFLE_STRATEGY_H