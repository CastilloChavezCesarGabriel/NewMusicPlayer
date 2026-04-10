#include "RepeatOneMode.h"

bool RepeatOneMode::apply(Cursor&) { return true; }

RepeatModeKind RepeatOneMode::identify() const {
    return RepeatModeKind::One;
}
