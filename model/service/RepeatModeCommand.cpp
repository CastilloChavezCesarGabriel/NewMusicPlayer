#include "RepeatModeCommand.h"

RepeatModeCommand::RepeatModeCommand(RepeatMode& repeat_mode) : repeat_mode_(repeat_mode) {}

void RepeatModeCommand::cycle() const {
    repeat_mode_.advance();
}