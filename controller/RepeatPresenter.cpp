#include "RepeatPresenter.h"

RepeatPresenter::RepeatPresenter(IRepeatDisplay& display) : display_(display) {}

void RepeatPresenter::onChanged(const RepeatModeKind kind) {
    display_.repeat(static_cast<int>(kind));
}