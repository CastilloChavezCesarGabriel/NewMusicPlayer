#ifndef TITLE_DESCENDING_SORT_H
#define TITLE_DESCENDING_SORT_H

#include "SortMode.h"

class TitleDescendingSort final : public SortMode {
public:
    TitleDescendingSort();
    void apply(Setlist& setlist) override;
    void reapply(Setlist& setlist) override;
};

#endif //TITLE_DESCENDING_SORT_H