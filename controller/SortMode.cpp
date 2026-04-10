#include "SortMode.h"

SortMode::SortMode(const std::string& label, ISortingAlgorithm* criteria)
    : label_(label), criteria_(criteria) {}

void SortMode::apply(Setlist& setlist) {
    setlist.sort(*criteria_);
}

void SortMode::display(IControlPanel& control) const {
    control.sort(label_);
}