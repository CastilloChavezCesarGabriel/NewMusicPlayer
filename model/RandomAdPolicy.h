#ifndef RANDOM_AD_POLICY_H
#define RANDOM_AD_POLICY_H

#include "IAdPolicy.h"
#include "IDice.h"

class RandomAdPolicy final : public IAdPolicy {
private:
    IDice& dice_;

public:
    explicit RandomAdPolicy(IDice& dice);
    bool decide() override;
    int clock() override;
    int pick(int max) override;
};

#endif //RANDOM_AD_POLICY_H
