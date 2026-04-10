#ifndef AD_RELAY_H
#define AD_RELAY_H

#include "../model/IAdListener.h"
#include "../model/IRepeatListener.h"
#include "../view/IControlPanel.h"

class AdRelay final : public IAdListener, public IRepeatListener {
private:
    IControlPanel& control_;

public:
    explicit AdRelay(IControlPanel& control);
    void onEnabled(bool state) override;
    void onSchedule(int delay) override;
    void onCancel() override;
    void onReveal(bool visible) override;
    void onRepeatChanged(RepeatModeKind kind) override;
};

#endif //AD_RELAY_H