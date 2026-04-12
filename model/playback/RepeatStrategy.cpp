#include "RepeatStrategy.h"

void RepeatStrategy::announce(IRepeatListener& listener) const {
    listener.onRepeatChanged(identify());
}