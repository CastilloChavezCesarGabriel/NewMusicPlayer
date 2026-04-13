#include "TitleDescending.h"
#include "../model/tracklist/QuickSort.h"
#include "../model/tracklist/ReverseArrangement.h"

TitleDescending::TitleDescending() : SortMode("Title \xe2\x96\xbc", new QuickSort()) {}

void TitleDescending::apply(Setlist& setlist) {
    setlist.sort(*criteria_);
    setlist.reverse();
}

void TitleDescending::reapply(Setlist& setlist) {
    ReverseArrangement descending;
    setlist.rearrange(*criteria_);
    setlist.rearrange(descending);
}