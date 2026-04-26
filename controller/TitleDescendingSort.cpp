#include "TitleDescendingSort.h"
#include "../model/tracklist/QuickSort.h"
#include "../model/tracklist/ReverseStrategy.h"

TitleDescendingSort::TitleDescendingSort() : SortMode("Title \xe2\x96\xbc", std::make_unique<QuickSort>()) {}

void TitleDescendingSort::apply(Setlist& setlist) {
    setlist.sort(*criteria_);
    setlist.reverse();
}

void TitleDescendingSort::reapply(Setlist& setlist) {
    ReverseStrategy descending;
    setlist.rearrange(*criteria_);
    setlist.rearrange(descending);
}