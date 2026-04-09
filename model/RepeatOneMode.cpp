#include "RepeatOneMode.h"

RepeatOneMode::RepeatOneMode() : RepeatStrategy(1) {}

bool RepeatOneMode::apply(Playlist&) { return true; }
