#include "RepeatController.h"

RepeatController::RepeatController(RepeatPolicy& repeatPolicy)
    : repeat_policy_(repeatPolicy) {}

void RepeatController::onRepeat() {
    repeat_policy_.advance();
}