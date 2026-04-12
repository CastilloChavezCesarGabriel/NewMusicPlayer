#include "RepeatOneMode.h"

bool RepeatOneMode::apply(TrackCursor&) { return true; }

RepeatModeKind RepeatOneMode::identify() const {
    return RepeatModeKind::One;
}