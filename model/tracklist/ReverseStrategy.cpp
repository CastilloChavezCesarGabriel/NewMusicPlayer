#include "ReverseStrategy.h"
#include <algorithm>
#include <ranges>

void ReverseStrategy::arrange(std::vector<Song>& songs) {
    std::ranges::reverse(songs);
}