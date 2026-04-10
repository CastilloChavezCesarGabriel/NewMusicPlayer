#include "RepeatBus.h"

void RepeatBus::add(IRepeatListener& listener) {
    listeners_.push_back(&listener);
}

void RepeatBus::notify(const std::function<void(IRepeatListener*)>& action) const {
    for (auto* listener : listeners_) {
        action(listener);
    }
}

void RepeatBus::onRepeatChanged(const RepeatModeKind kind) {
    notify([&](IRepeatListener* listener) { listener->onRepeatChanged(kind); });
}
