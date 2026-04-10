#include "AdRelay.h"

AdRelay::AdRelay(IControlPanel& control)
    : control_(control) {}

void AdRelay::onEnabled(const bool state) {
    control_.enable(state);
}

void AdRelay::onSchedule(const int delay) {
    control_.schedule(delay);
}

void AdRelay::onCancel() {
    control_.cancel();
}

void AdRelay::onReveal(const bool visible) {
    control_.reveal(visible);
}

void AdRelay::onRepeatChanged(const RepeatModeKind kind) {
    control_.repeat(static_cast<int>(kind));
}