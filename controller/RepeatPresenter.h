#ifndef REPEAT_PRESENTER_H
#define REPEAT_PRESENTER_H

#include "../model/playback/IRepeatListener.h"
#include "../view/IRepeatDisplay.h"

class RepeatPresenter final : public IRepeatListener {
private:
    IRepeatDisplay& display_;

public:
    explicit RepeatPresenter(IRepeatDisplay& display);
    void onChanged(RepeatModeKind kind) override;
};

#endif