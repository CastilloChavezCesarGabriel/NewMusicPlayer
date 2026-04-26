#ifndef REVERSE_STRATEGY_H
#define REVERSE_STRATEGY_H

#include "IArrangementStrategy.h"

class ReverseStrategy final : public IArrangementStrategy {
public:
    void arrange(std::vector<Song>& songs) override;
};

#endif //REVERSE_STRATEGY_H