#include "AdBus.h"

void AdBus::onEnable(const bool state) {
    broadcast([&](IAdListener& listener) { listener.onEnable(state); });
}

void AdBus::onSchedule(const int delay) {
    broadcast([&](IAdListener& listener) { listener.onSchedule(delay); });
}

void AdBus::onCancel() {
    broadcast([](IAdListener& listener) { listener.onCancel(); });
}

void AdBus::onReveal(const bool visible) {
    broadcast([&](IAdListener& listener) { listener.onReveal(visible); });
}