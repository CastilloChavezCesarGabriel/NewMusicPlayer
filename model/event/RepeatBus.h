#ifndef REPEAT_BUS_H
#define REPEAT_BUS_H

#include "Bus.h"
#include "../playback/IRepeatListener.h"

class RepeatBus final : public Bus<IRepeatListener>, public IRepeatListener {
public:
    void onRepeatChanged(RepeatModeKind kind) override;
};

#endif //REPEAT_BUS_H