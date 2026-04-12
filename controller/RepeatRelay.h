#ifndef REPEAT_RELAY_H
#define REPEAT_RELAY_H

#include "../model/playback/IRepeatListener.h"
#include "../view/IRepeatDisplay.h"

class RepeatRelay final : public IRepeatListener {
private:
    IRepeatDisplay& display_;

public:
    explicit RepeatRelay(IRepeatDisplay& display);
    void onRepeatChanged(RepeatModeKind kind) override;
};

#endif
