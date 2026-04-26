#include "OrderingController.h"

OrderingController::OrderingController(Setlist& setlist, ISortDisplay& sortDisplay)
    : setlist_(setlist), sort_display_(sortDisplay) {}

void OrderingController::add(std::unique_ptr<SortMode> mode) {
    modes_.push_back(std::move(mode));
}

void OrderingController::onSort() {
    mode_index_ = (mode_index_ + 1) % static_cast<int>(modes_.size());
    modes_[mode_index_]->apply(setlist_);
    modes_[mode_index_]->display(sort_display_);
    setlist_.announce();
}

void OrderingController::onShuffle() {
    setlist_.shuffle();
    setlist_.announce();
}

void OrderingController::refresh() const {
    if (mode_index_ >= 0) {
        modes_[mode_index_]->apply(setlist_);
    }
}