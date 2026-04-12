#include "ReverseArrangement.h"
#include <algorithm>
#include <ranges>

void ReverseArrangement::arrange(std::vector<Song>& songs) {
    std::ranges::reverse(songs);
}