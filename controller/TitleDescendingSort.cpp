#include "TitleDescendingSort.h"
#include "../model/tracklist/QuickSort.h"

TitleDescendingSort::TitleDescendingSort() : SortMode("Title \xe2\x96\xbc", std::make_unique<QuickSort>()) {}

void TitleDescendingSort::apply(Setlist& setlist) {
    SortMode::apply(setlist);
    setlist.reverse();
}