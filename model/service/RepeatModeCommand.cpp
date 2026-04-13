#include "RepeatModeCommand.h"

RepeatModeCommand::RepeatModeCommand(RepeatMode& repeatMode) : repeat_mode_(repeatMode) {}

void RepeatModeCommand::cycle() const {
    repeat_mode_.advance();
}