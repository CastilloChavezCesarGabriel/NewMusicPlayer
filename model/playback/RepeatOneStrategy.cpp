#include "RepeatOneStrategy.h"

bool RepeatOneStrategy::apply(TrackCursor&) { return true; }

RepeatModeKind RepeatOneStrategy::identify() const {
    return RepeatModeKind::One;
}