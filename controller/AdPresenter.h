#ifndef AD_PRESENTER_H
#define AD_PRESENTER_H

#include "../model/playback/IAdListener.h"
#include "../view/IEnableable.h"
#include "../view/ITimingPanel.h"
#include "../view/IToolbarDisplay.h"

class AdPresenter final : public IAdListener {
private:
    IEnableable& enable_;
    ITimingPanel& timing_;
    IToolbarDisplay& toolbar_;

public:
    AdPresenter(IEnableable& enable, ITimingPanel& timing, IToolbarDisplay& toolbar);
    void onEnable(bool state) override;
    void onSchedule(int delay) override;
    void onCancel() override;
    void onReveal(bool visible) override;
};

#endif //AD_PRESENTER_H