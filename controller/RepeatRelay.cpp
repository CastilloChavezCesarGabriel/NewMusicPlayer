#include "RepeatRelay.h"

RepeatRelay::RepeatRelay(IRepeatDisplay& display) : display_(display) {}

void RepeatRelay::onChanged(const RepeatModeKind kind) {
    display_.repeat(static_cast<int>(kind));
}