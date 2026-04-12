#ifndef ORIGINAL_ORDER_H
#define ORIGINAL_ORDER_H

#include "../song/Song.h"
#include <vector>

class OriginalOrder {
private:
    std::vector<Song> snapshot_;

public:
    void preserve(const std::vector<Song>& songs);
    void restore(std::vector<Song>& songs);
};

#endif //ORIGINAL_ORDER_H