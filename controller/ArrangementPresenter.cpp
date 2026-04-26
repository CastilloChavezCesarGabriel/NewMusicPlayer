#include "ArrangementPresenter.h"

ArrangementPresenter::ArrangementPresenter(OrderingController& ordering)
    : ordering_(ordering) {}

void ArrangementPresenter::onChanged() {
    ordering_.refresh();
}

void ArrangementPresenter::onFeedback(const std::string&, bool) {}