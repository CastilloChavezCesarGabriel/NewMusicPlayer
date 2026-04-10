#include "ArrangementController.h"
#include "TitleDescending.h"
#include "CustomMode.h"
#include "../model/QuickSort.h"
#include "../model/DurationSort.h"
#include "../model/DateSort.h"

ArrangementController::ArrangementController(Setlist& setlist, RepeatSwitch& repeat_switch, ISortDisplay& sort_display)
    : setlist_(setlist), repeat_switch_(repeat_switch), sort_display_(sort_display) {
    modes_.push_back(std::make_unique<SortMode>("Title \xe2\x96\xb2", new QuickSort()));
    modes_.push_back(std::make_unique<TitleDescending>());
    modes_.push_back(std::make_unique<SortMode>("Duration \xe2\x96\xb2", new DurationSort()));
    modes_.push_back(std::make_unique<SortMode>("Date \xe2\x96\xb2", new DateSort()));
    modes_.push_back(std::make_unique<CustomMode>());
}

void ArrangementController::onSort() {
    index_ = (index_ + 1) % static_cast<int>(modes_.size());
    modes_[index_]->apply(setlist_);
    modes_[index_]->display(sort_display_);
}

void ArrangementController::onShuffle() {
    setlist_.shuffle();
}

void ArrangementController::onRepeat() {
    repeat_switch_.cycle();
}
