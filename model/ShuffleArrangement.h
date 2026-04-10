#ifndef SHUFFLE_ARRANGEMENT_H
#define SHUFFLE_ARRANGEMENT_H

#include "IArrangementStrategy.h"

class ShuffleArrangement final : public IArrangementStrategy {
public:
    void arrange(std::vector<Song>& songs) override;
};

#endif //SHUFFLE_ARRANGEMENT_H
