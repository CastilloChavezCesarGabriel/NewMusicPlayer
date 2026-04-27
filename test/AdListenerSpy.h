#ifndef AD_LISTENER_SPY_H
#define AD_LISTENER_SPY_H

#include "../model/playback/IAdListener.h"

class AdListenerSpy final : public IAdListener {
private:
    int reveals_ = 0;

public:
    void onEnable(bool state) override;
    void onReveal(bool visible) override;
    void onSchedule(int delay) override;
    void onCancel() override;

    void expectNoReveal() const;
};

#endif //AD_LISTENER_SPY_H