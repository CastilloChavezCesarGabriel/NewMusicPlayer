#ifndef AD_BUS_H
#define AD_BUS_H

#include "IAdListener.h"
#include <vector>
#include <functional>

class AdBus final : public IAdListener {
private:
    std::vector<IAdListener*> listeners_;
    void notify(const std::function<void(IAdListener*)>& action) const;

public:
    void add(IAdListener& listener);
    void onEnabled(bool state) override;
    void onSchedule(int delay) override;
    void onCancel() override;
    void onReveal(bool visible) override;
};

#endif //AD_BUS_H