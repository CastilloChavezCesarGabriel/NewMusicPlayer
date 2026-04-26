#include "ShuffleStrategy.h"
#include <algorithm>
#include <random>
#include <ranges>

void ShuffleStrategy::arrange(std::vector<Song>& songs) {
    static std::random_device device;
    static std::mt19937 generator(device());
    std::ranges::shuffle(songs, generator);
}