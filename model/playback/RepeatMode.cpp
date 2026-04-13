#include "RepeatMode.h"
#include "NoRepeatMode.h"
#include "RepeatOneMode.h"
#include "RepeatAllMode.h"

RepeatMode::RepeatMode(TrackCursor& cursor, RepeatCoordinator& listener)
    : cursor_(cursor), listener_(listener) {
    modes_.push_back(std::make_unique<NoRepeatMode>());
    modes_.push_back(std::make_unique<RepeatOneMode>());
    modes_.push_back(std::make_unique<RepeatAllMode>());
}

void RepeatMode::advance() {
    mode_index_ = (mode_index_ + 1) % static_cast<int>(modes_.size());
    modes_[mode_index_]->announce(listener_);
}

bool RepeatMode::apply() const {
    return modes_[mode_index_]->apply(cursor_);
}

void RepeatMode::stop() const {
    listener_.stop();
}