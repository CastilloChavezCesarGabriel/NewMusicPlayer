#ifndef RANDOM_AD_POLICY_H
#define RANDOM_AD_POLICY_H

#include "IAdPolicy.h"
#include "../library/IDice.h"

class RandomAdPolicy final : public IAdPolicy {
private:
    static constexpr int AD_PROBABILITY_PERCENT = 25;
    static constexpr int PERCENTAGE_DIE_FACES = 100;
    static constexpr int AD_DELAY_BASE_SECONDS = 4;
    static constexpr int AD_DELAY_JITTER_DIE_FACES = 6;
    static constexpr int SECONDS_TO_MILLIS = 1000;

    IDice& dice_;

public:
    explicit RandomAdPolicy(IDice& dice);
    bool decide() override;
    int clock() override;
    int pick(int totalAds) override;
};

#endif //RANDOM_AD_POLICY_H
