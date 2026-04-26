#include "ArrangementPresenter.h"

ArrangementPresenter::ArrangementPresenter(PlaybackModeController& arrangement)
    : arrangement_(arrangement) {}

void ArrangementPresenter::onChanged() {
    arrangement_.refresh();
}

void ArrangementPresenter::onFeedback(const std::string&, bool) {}