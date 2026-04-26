#ifndef ARRANGEMENT_CONTROLLER_H
#define ARRANGEMENT_CONTROLLER_H

#include "SortMode.h"
#include <vector>
#include <memory>
#include "../model/service/Setlist.h"
#include "../model/playback/RepeatPolicy.h"
#include "../view/IArrangementControl.h"
#include "../view/ISortDisplay.h"

class ArrangementController final : public IArrangementControl {
private:
    Setlist& setlist_;
    RepeatPolicy& repeat_mode_;
    ISortDisplay& sort_display_;
    std::vector<std::unique_ptr<SortMode>> modes_;
    int mode_index_ = -1;

public:
    ArrangementController(Setlist& setlist, RepeatPolicy& repeatMode, ISortDisplay& sortDisplay);
    void add(std::unique_ptr<SortMode> mode);
    void onSort() override;
    void onShuffle() override;
    void onRepeat() override;
    void refresh();
};

#endif //ARRANGEMENT_CONTROLLER_H
