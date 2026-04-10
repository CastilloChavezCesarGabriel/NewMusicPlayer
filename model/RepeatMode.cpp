#include "RepeatMode.h"
#include "NoRepeatMode.h"
#include "RepeatOneMode.h"
#include "RepeatAllMode.h"

RepeatMode::RepeatMode(Cursor& cursor, RepeatListener& listener)
    : cursor_(cursor), listener_(listener) {
    modes_.push_back(std::make_unique<NoRepeatMode>());
    modes_.push_back(std::make_unique<RepeatOneMode>());
    modes_.push_back(std::make_unique<RepeatAllMode>());
}

void RepeatMode::advance() {
    index_ = (index_ + 1) % static_cast<int>(modes_.size());
    modes_[index_]->announce(listener_);
}

bool RepeatMode::apply() const {
    return modes_[index_]->apply(cursor_);
}

void RepeatMode::stop() const {
    listener_.stop();
}
