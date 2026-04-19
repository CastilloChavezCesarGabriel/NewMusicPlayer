#include "ArrangementController.h"

ArrangementController::ArrangementController(Setlist& setlist, RepeatMode& repeatMode, ISortDisplay& sortDisplay)
    : setlist_(setlist), repeat_mode_(repeatMode), sort_display_(sortDisplay) {}

void ArrangementController::add(std::unique_ptr<SortMode> mode) {
    modes_.push_back(std::move(mode));
}

void ArrangementController::onSort() {
    mode_index_ = (mode_index_ + 1) % static_cast<int>(modes_.size());
    modes_[mode_index_]->apply(setlist_);
    modes_[mode_index_]->display(sort_display_);
}

void ArrangementController::onShuffle() {
    setlist_.shuffle();
}

void ArrangementController::onRepeat() {
    repeat_mode_.advance();
}

void ArrangementController::refresh() {
    if (mode_index_ >= 0) {
        modes_[mode_index_]->reapply(setlist_);
    }
}
