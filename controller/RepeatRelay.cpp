#include "RepeatRelay.h"

RepeatRelay::RepeatRelay(IRepeatDisplay& display) : display_(display) {}

void RepeatRelay::onRepeatChanged(const RepeatModeKind kind) {
    display_.repeat(static_cast<int>(kind));
}