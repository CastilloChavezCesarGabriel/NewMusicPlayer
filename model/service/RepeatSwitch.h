#ifndef REPEAT_SWITCH_H
#define REPEAT_SWITCH_H

#include "../RepeatMode.h"

class RepeatSwitch {
private:
    RepeatMode& repeat_mode_;

public:
    explicit RepeatSwitch(RepeatMode& repeat_mode);

    void cycle() const;
};

#endif //REPEAT_SWITCH_H