#include "ArrangementRelay.h"

ArrangementRelay::ArrangementRelay(IRefreshable& arrangement)
    : arrangement_(arrangement) {}

void ArrangementRelay::onChanged() {
    arrangement_.refresh();
}

void ArrangementRelay::onFeedback(const std::string&, bool) {}