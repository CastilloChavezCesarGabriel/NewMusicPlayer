#ifndef REPEAT_CONTROLLER_H
#define REPEAT_CONTROLLER_H

#include "../model/playback/RepeatPolicy.h"
#include "../view/IRepeatControl.h"

class RepeatController final : public IRepeatControl {
private:
    RepeatPolicy& repeat_policy_;

public:
    explicit RepeatController(RepeatPolicy& repeatPolicy);
    void onRepeat() override;
};

#endif //REPEAT_CONTROLLER_H