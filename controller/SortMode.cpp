#include "SortMode.h"

SortMode::SortMode(const std::string& label, IArrangementStrategy* criteria)
    : label_(label), criteria_(criteria) {}

void SortMode::apply(Setlist& setlist) {
    setlist.sort(*criteria_);
}

void SortMode::reapply(Setlist& setlist) {
    setlist.rearrange(*criteria_);
}

void SortMode::display(ISortDisplay& sort_display) const {
    sort_display.sort(label_);
}