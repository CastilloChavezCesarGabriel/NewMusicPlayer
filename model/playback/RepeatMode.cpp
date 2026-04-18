#include "RepeatMode.h"

RepeatMode::RepeatMode(TrackCursor& cursor, RepeatCoordinator& listener)
    : cursor_(cursor), listener_(listener) {}

void RepeatMode::add(std::unique_ptr<RepeatStrategy> strategy) {
    modes_.push_back(std::move(strategy));
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