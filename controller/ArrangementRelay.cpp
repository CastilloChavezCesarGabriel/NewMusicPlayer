#include "ArrangementRelay.h"

ArrangementRelay::ArrangementRelay(ArrangementController& arrangement)
    : arrangement_(arrangement) {}

void ArrangementRelay::onChanged() {
    arrangement_.refresh();
}

void ArrangementRelay::onFeedback(const std::string&, bool) {}