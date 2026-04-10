#ifndef I_AD_LISTENER_H
#define I_AD_LISTENER_H

class IAdListener {
public:
    virtual ~IAdListener() = default;
    virtual void onEnabled(bool state) = 0;
    virtual void onSchedule(int delay) = 0;
    virtual void onCancel() = 0;
    virtual void onReveal(bool visible) = 0;
};

#endif //I_AD_LISTENER_H
