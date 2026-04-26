#include "TitleDescendingSort.h"
#include "../model/tracklist/QuickSort.h"
#include "../model/tracklist/ReverseArrangement.h"

TitleDescendingSort::TitleDescendingSort() : SortMode("Title \xe2\x96\xbc", new QuickSort()) {}

void TitleDescendingSort::apply(Setlist& setlist) {
    setlist.sort(*criteria_);
    setlist.reverse();
}

void TitleDescendingSort::reapply(Setlist& setlist) {
    ReverseArrangement descending;
    setlist.rearrange(*criteria_);
    setlist.rearrange(descending);
}