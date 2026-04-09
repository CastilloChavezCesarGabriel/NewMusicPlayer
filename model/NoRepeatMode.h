#ifndef NO_REPEAT_MODE_H
#define NO_REPEAT_MODE_H

#include "RepeatStrategy.h"

class NoRepeatMode final : public RepeatStrategy {
public:
    NoRepeatMode();
    bool apply(Playlist& playlist) override;
};

#endif //NO_REPEAT_MODE_H