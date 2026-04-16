#include "RepeatBus.h"

void RepeatBus::onChanged(const RepeatModeKind kind) {
    broadcast([&](IRepeatListener& listener) { listener.onChanged(kind); });
}