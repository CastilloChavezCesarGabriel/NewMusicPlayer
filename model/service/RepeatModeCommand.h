#ifndef REPEAT_MODE_COMMAND_H
#define REPEAT_MODE_COMMAND_H

#include "../playback/RepeatMode.h"

class RepeatModeCommand {
private:
    RepeatMode& repeat_mode_;

public:
    explicit RepeatModeCommand(RepeatMode& repeatMode);

    void cycle() const;
};

#endif //REPEAT_MODE_COMMAND_H