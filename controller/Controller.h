#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/service/Playback.h"
#include "../model/service/Library.h"
#include "../model/service/Setlist.h"
#include "../model/service/Catalog.h"
#include "../model/service/RepeatSwitch.h"
#include "../model/ITrackListener.h"
#include "../model/ILibraryListener.h"
#include "../model/IAdListener.h"
#include "../model/IRepeatListener.h"
#include "../view/IPlayerView.h"
#include "../view/IPlayerListener.h"
#include "SortController.h"
#include "SearchController.h"

class Controller final : public ITrackListener,
                         public ILibraryListener,
                         public IAdListener,
                         public IRepeatListener,
                         public IPlayerListener {
private:
    Playback& playback_;
    Library& library_;
    Setlist& setlist_;
    Catalog& catalog_;
    RepeatSwitch& repeat_switch_;
    IPlayerView& view_;
    SortController sort_;
    SearchController search_;
    bool playing_ = false;

    void refresh() const;

public:
    Controller(Playback& playback,
               Library& library,
               Setlist& setlist,
               Catalog& catalog,
               RepeatSwitch& repeat_switch,
               IPlayerView& view);

    void onStart(const std::string& path) override;
    void onSelected(int index) override;
    void onStopped() override;
    void onChanged() override;
    void onFeedback(const std::string& message, bool success) override;
    void onEnabled(bool state) override;
    void onReveal(bool visible) override;
    void onSchedule(int delay) override;
    void onCancel() override;
    void onRepeatChanged(RepeatModeKind kind) override;
    void onPlay(int index) override;
    void onToggle() override;
    void onRepeat() override;
    void onAdvance() override;
    void onRetreat() override;
    void onAdd() override;
    void onRemove(int index) override;
    void onShuffle() override;
    void onSkip() override;
    void onSort() override;
    void onSearch(const std::string& query) override;
    void onPick(const std::string& name) override;
    void onDrop(const std::vector<std::string>& paths) override;
    void onAdjust(int volume) override;
    void onEnd() override;
};

#endif //CONTROLLER_H
