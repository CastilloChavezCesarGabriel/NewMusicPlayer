#ifndef TITLE_DESCENDING_H
#define TITLE_DESCENDING_H

#include "SortMode.h"

class TitleDescending final : public SortMode {
public:
    TitleDescending();
    void apply(Setlist& setlist) override;
    void reapply(Setlist& setlist) override;
};

#endif //TITLE_DESCENDING_H