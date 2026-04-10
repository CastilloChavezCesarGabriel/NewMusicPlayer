#ifndef ARRANGEMENT_CONTROLLER_H
#define ARRANGEMENT_CONTROLLER_H

#include "SortMode.h"
#include <vector>
#include <memory>
#include "../model/service/Setlist.h"
#include "../model/service/RepeatSwitch.h"
#include "../view/IArrangementControl.h"
#include "../view/IControlPanel.h"

class ArrangementController final : public IArrangementControl {
private:
    Setlist& setlist_;
    RepeatSwitch& repeat_switch_;
    IControlPanel& control_;
    std::vector<std::unique_ptr<SortMode>> modes_;
    int index_ = -1;

public:
    ArrangementController(Setlist& setlist, RepeatSwitch& repeat_switch, IControlPanel& control);
    void onSort() override;
    void onShuffle() override;
    void onRepeat() override;
};

#endif //ARRANGEMENT_CONTROLLER_H