#ifndef I_AD_POLICY_H
#define I_AD_POLICY_H

class IAdPolicy {
public:
    virtual ~IAdPolicy() = default;
    virtual bool decide() = 0;
    virtual int clock() = 0;
    virtual int pick(int max) = 0;
};

#endif //I_AD_POLICY_H