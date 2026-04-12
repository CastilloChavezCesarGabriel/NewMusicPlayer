#include "EnableCoordinator.h"

void EnableCoordinator::add(IEnableable& target) { targets_.push_back(&target); }

void EnableCoordinator::enable(const bool state) {
    for (auto* target : targets_) target->enable(state);
}