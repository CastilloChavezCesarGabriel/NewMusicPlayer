#ifndef PLAYBACK_MODE_CONTROLLER_H
#define PLAYBACK_MODE_CONTROLLER_H

#include "SortMode.h"
#include <vector>
#include <memory>
#include "../model/service/Setlist.h"
#include "../model/playback/RepeatPolicy.h"
#include "../view/IArrangementControl.h"
#include "../view/ISortDisplay.h"

class PlaybackModeController final : public IArrangementControl {
private:
    Setlist& setlist_;
    RepeatPolicy& repeat_policy_;
    ISortDisplay& sort_display_;
    std::vector<std::unique_ptr<SortMode>> modes_;
    int mode_index_ = -1;

public:
    PlaybackModeController(Setlist& setlist, RepeatPolicy& repeatPolicy, ISortDisplay& sortDisplay);
    void add(std::unique_ptr<SortMode> mode);
    void onSort() override;
    void onShuffle() override;
    void onRepeat() override;
    void refresh();
};

#endif //PLAYBACK_MODE_CONTROLLER_H
