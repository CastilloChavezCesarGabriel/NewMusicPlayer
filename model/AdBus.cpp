#include "AdBus.h"

void AdBus::add(IAdListener& listener) {
    listeners_.push_back(&listener);
}

void AdBus::notify(const std::function<void(IAdListener*)>& action) const {
    for (auto* listener : listeners_) {
        action(listener);
    }
}

void AdBus::onEnabled(const bool state) {
    notify([&](IAdListener* listener) { listener->onEnabled(state); });
}

void AdBus::onSchedule(const int delay) {
    notify([&](IAdListener* listener) { listener->onSchedule(delay); });
}

void AdBus::onCancel() {
    notify([](IAdListener* listener) { listener->onCancel(); });
}

void AdBus::onReveal(const bool visible) {
    notify([&](IAdListener* listener) { listener->onReveal(visible); });
}