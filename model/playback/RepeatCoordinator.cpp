#include "RepeatCoordinator.h"

RepeatCoordinator::RepeatCoordinator(IRepeatListener& repeats, ITrackListener& tracks)
    : repeats_(repeats), tracks_(tracks) {}

void RepeatCoordinator::onRepeatChanged(const RepeatModeKind kind) {
    repeats_.onRepeatChanged(kind);
}

void RepeatCoordinator::stop() const {
    tracks_.onStopped();
}