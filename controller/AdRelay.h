#ifndef AD_RELAY_H
#define AD_RELAY_H

#include "../model/playback/IAdListener.h"
#include "../view/IEnableable.h"
#include "../view/ITimingPanel.h"
#include "../view/IToolbarDisplay.h"

class AdRelay final : public IAdListener {
private:
    IEnableable& enable_;
    ITimingPanel& timing_;
    IToolbarDisplay& toolbar_;

public:
    AdRelay(IEnableable& enable, ITimingPanel& timing, IToolbarDisplay& toolbar);
    void onEnabled(bool state) override;
    void onSchedule(int delay) override;
    void onCancel() override;
    void onReveal(bool visible) override;
};

#endif //AD_RELAY_H