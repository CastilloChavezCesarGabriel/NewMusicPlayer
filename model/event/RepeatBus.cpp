#include "RepeatBus.h"

void RepeatBus::onRepeatChanged(const RepeatModeKind kind) {
    broadcast([&](IRepeatListener& listener) { listener.onRepeatChanged(kind); });
}