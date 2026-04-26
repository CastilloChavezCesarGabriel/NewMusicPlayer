#ifndef ORDERING_CONTROLLER_H
#define ORDERING_CONTROLLER_H

#include "SortMode.h"
#include <vector>
#include <memory>
#include "../model/service/Setlist.h"
#include "../view/IOrderControl.h"
#include "../view/ISortDisplay.h"

class OrderingController final : public IOrderControl {
private:
    Setlist& setlist_;
    ISortDisplay& sort_display_;
    std::vector<std::unique_ptr<SortMode>> modes_;
    int mode_index_ = -1;

public:
    OrderingController(Setlist& setlist, ISortDisplay& sortDisplay);
    void add(std::unique_ptr<SortMode> mode);
    void onSort() override;
    void onShuffle() override;
    void refresh() const;
};

#endif //ORDERING_CONTROLLER_H