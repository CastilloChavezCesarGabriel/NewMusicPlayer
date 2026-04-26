#include "PlaybackModeController.h"

PlaybackModeController::PlaybackModeController(Setlist& setlist, RepeatPolicy& repeatMode, ISortDisplay& sortDisplay)
    : setlist_(setlist), repeat_mode_(repeatMode), sort_display_(sortDisplay) {}

void PlaybackModeController::add(std::unique_ptr<SortMode> mode) {
    modes_.push_back(std::move(mode));
}

void PlaybackModeController::onSort() {
    mode_index_ = (mode_index_ + 1) % static_cast<int>(modes_.size());
    modes_[mode_index_]->apply(setlist_);
    modes_[mode_index_]->display(sort_display_);
}

void PlaybackModeController::onShuffle() {
    setlist_.shuffle();
}

void PlaybackModeController::onRepeat() {
    repeat_mode_.advance();
}

void PlaybackModeController::refresh() {
    if (mode_index_ >= 0) {
        modes_[mode_index_]->reapply(setlist_);
    }
}
