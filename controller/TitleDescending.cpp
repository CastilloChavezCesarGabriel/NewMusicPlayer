#include "TitleDescending.h"
#include "../model/QuickSort.h"

TitleDescending::TitleDescending() : SortMode("Title \xe2\x96\xbc", new QuickSort()) {}

void TitleDescending::apply(Setlist& setlist) {
    setlist.sort(*criteria_);
    setlist.reverse();
}