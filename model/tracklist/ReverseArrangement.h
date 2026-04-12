#ifndef REVERSE_ARRANGEMENT_H
#define REVERSE_ARRANGEMENT_H

#include "IArrangementStrategy.h"

class ReverseArrangement final : public IArrangementStrategy {
public:
    void arrange(std::vector<Song>& songs) override;
};

#endif //REVERSE_ARRANGEMENT_H