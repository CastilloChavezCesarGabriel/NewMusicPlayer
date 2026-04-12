#include "RepeatListener.h"

RepeatListener::RepeatListener(IRepeatListener& repeats, ITrackListener& tracks)
    : repeats_(repeats), tracks_(tracks) {}

void RepeatListener::onRepeatChanged(const RepeatModeKind kind) {
    repeats_.onRepeatChanged(kind);
}

void RepeatListener::stop() const {
    tracks_.onStopped();
}