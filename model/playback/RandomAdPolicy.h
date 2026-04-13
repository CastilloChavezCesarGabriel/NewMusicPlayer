#ifndef RANDOM_AD_POLICY_H
#define RANDOM_AD_POLICY_H

#include "IAdPolicy.h"
#include "../library/IDice.h"

class RandomAdPolicy final : public IAdPolicy {
private:
    IDice& dice_;

public:
    explicit RandomAdPolicy(IDice& dice);
    bool decide() override;
    int clock() override;
    int pick(int totalAds) override;
};

#endif //RANDOM_AD_POLICY_H