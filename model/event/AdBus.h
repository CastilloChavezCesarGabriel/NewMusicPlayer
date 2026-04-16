#ifndef AD_BUS_H
#define AD_BUS_H

#include "Bus.h"
#include "../playback/IAdListener.h"

class AdBus final : public Bus<IAdListener>, public IAdListener {
public:
    void onEnable(bool state) override;
    void onSchedule(int delay) override;
    void onCancel() override;
    void onReveal(bool visible) override;
};

#endif //AD_BUS_H