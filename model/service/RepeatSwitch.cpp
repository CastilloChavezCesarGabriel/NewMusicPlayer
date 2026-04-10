#include "RepeatSwitch.h"

RepeatSwitch::RepeatSwitch(RepeatMode& repeat_mode) : repeat_mode_(repeat_mode) {}

void RepeatSwitch::cycle() const {
    repeat_mode_.advance();
}