#include "RepeatCoordinator.h"

RepeatCoordinator::RepeatCoordinator(IRepeatListener& repeats, ITrackListener& tracks)
    : repeats_(repeats), tracks_(tracks) {}

void RepeatCoordinator::onChanged(const RepeatModeKind kind) {
    repeats_.onChanged(kind);
}

void RepeatCoordinator::stop() const {
    tracks_.onStop();
}