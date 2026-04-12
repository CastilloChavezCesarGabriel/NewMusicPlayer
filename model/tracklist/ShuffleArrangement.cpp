#include "ShuffleArrangement.h"
#include <algorithm>
#include <random>
#include <ranges>

void ShuffleArrangement::arrange(std::vector<Song>& songs) {
    static std::random_device device;
    static std::mt19937 generator(device());
    std::ranges::shuffle(songs, generator);
}