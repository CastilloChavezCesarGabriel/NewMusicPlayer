#include "RandomAdPolicy.h"

RandomAdPolicy::RandomAdPolicy(IDice& dice) : dice_(dice) {}

bool RandomAdPolicy::decide() {
    return dice_.roll(PERCENTAGE_DIE_FACES) <= AD_PROBABILITY_PERCENT;
}

int RandomAdPolicy::clock() {
    return (dice_.roll(AD_DELAY_JITTER_DIE_FACES) + AD_DELAY_BASE_SECONDS) * SECONDS_TO_MILLIS;
}

int RandomAdPolicy::pick(const int totalAds) {
    return dice_.roll(totalAds) - 1;
}
