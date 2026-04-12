#ifndef ARRANGEMENT_CONTROLLER_H
#define ARRANGEMENT_CONTROLLER_H

#include "SortMode.h"
#include <vector>
#include <memory>
#include "../model/service/Setlist.h"
#include "../model/service/RepeatModeCommand.h"
#include "../view/IArrangementControl.h"
#include "../view/ISortDisplay.h"

class ArrangementController final : public IArrangementControl {
private:
    Setlist& setlist_;
    RepeatModeCommand& repeat_switch_;
    ISortDisplay& sort_display_;
    std::vector<std::unique_ptr<SortMode>> modes_;
    int index_ = -1;

public:
    ArrangementController(Setlist& setlist, RepeatModeCommand& repeat_switch, ISortDisplay& sort_display);
    void onSort() override;
    void onShuffle() override;
    void onRepeat() override;
};

#endif //ARRANGEMENT_CONTROLLER_H
