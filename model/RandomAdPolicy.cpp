#include "RandomAdPolicy.h"

RandomAdPolicy::RandomAdPolicy(IDice& dice) : dice_(dice) {}

bool RandomAdPolicy::decide() {
    return dice_.roll(100) <= 25;
}

int RandomAdPolicy::clock() {
    return (dice_.roll(6) + 4) * 1000;
}

int RandomAdPolicy::pick(const int max) {
    return dice_.roll(max) - 1;
}