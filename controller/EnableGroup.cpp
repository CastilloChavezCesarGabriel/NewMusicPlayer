#include "EnableGroup.h"

void EnableGroup::add(IEnableable& target) { targets_.push_back(&target); }

void EnableGroup::enable(const bool state) {
    for (auto* target : targets_) target->enable(state);
}