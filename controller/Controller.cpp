#include "Controller.h"
#include "PlaylistRenderer.h"

Controller::Controller(Playback& playback,
                       Library& library,
                       Setlist& setlist,
                       Catalog& catalog,
                       RepeatSwitch& repeat_switch,
                       IPlayerView& view)
    : playback_(playback),
      library_(library),
      setlist_(setlist),
      catalog_(catalog),
      repeat_switch_(repeat_switch),
      view_(view),
      sort_(setlist, view),
      search_(catalog, view) {
    view_.add(this);
    refresh();
}

void Controller::onStart(const std::string& path) {
    view_.play(path);
    playing_ = true;
}

void Controller::onChanged() {
    refresh();
}

void Controller::onSelected(const int index) {
    view_.highlight(index);
    view_.enable(true);
}

void Controller::onEnabled(const bool state) {
    view_.enable(state);
}

void Controller::onReveal(const bool visible) {
    view_.reveal(visible);
}

void Controller::onSchedule(const int delay) {
    view_.schedule(delay);
}

void Controller::onCancel() {
    view_.cancel();
}

void Controller::onRepeatChanged(const RepeatModeKind kind) {
    view_.repeat(static_cast<int>(kind));
}

void Controller::onFeedback(const std::string& message, const bool success) {
    view_.notify(message, success);
}

void Controller::onStopped() {
    view_.enable(false);
    view_.pause();
    view_.highlight(-1);
    playing_ = false;
}

void Controller::onPlay(const int index) {
    playback_.play(index);
}

void Controller::onToggle() {
    if (playing_) {
        view_.pause();
    } else {
        view_.resume();
    }
    playing_ = !playing_;
}

void Controller::onRepeat() {
    repeat_switch_.cycle();
}

void Controller::onAdvance() {
    playback_.advance();
}

void Controller::onRetreat() {
    playback_.retreat();
}

void Controller::onAdd() {
    const std::string path = view_.browse();
    if (!path.empty()) {
        library_.insert(path);
    }
}

void Controller::onRemove(const int index) {
    if (view_.confirm("Are you sure you wanna delete this song?")) {
        library_.remove(index);
    }
}

void Controller::onShuffle() {
    setlist_.shuffle();
}

void Controller::onSkip() {
    playback_.skip();
}

void Controller::onSort() {
    sort_.cycle();
}

void Controller::onSearch(const std::string& query) {
    search_.search(query);
}

void Controller::onPick(const std::string& name) {
    playback_.pick(name);
    view_.dismiss();
}

void Controller::onDrop(const std::vector<std::string>& paths) {
    for (const auto& path : paths) {
        library_.insert(path);
    }
}

void Controller::onAdjust(const int volume) {
    view_.adjust(volume);
}

void Controller::onEnd() {
    playback_.end();
}

void Controller::refresh() const {
    PlaylistRenderer renderer(view_);
    catalog_.accept(renderer);
    renderer.render();
}
