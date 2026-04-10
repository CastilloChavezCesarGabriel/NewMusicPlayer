#ifndef REPEAT_BUS_H
#define REPEAT_BUS_H

#include "IRepeatListener.h"
#include <vector>
#include <functional>

class RepeatBus final : public IRepeatListener {
private:
    std::vector<IRepeatListener*> listeners_;
    void notify(const std::function<void(IRepeatListener*)>& action) const;

public:
    void add(IRepeatListener& listener);
    void onRepeatChanged(RepeatModeKind kind) override;
};

#endif //REPEAT_BUS_H
