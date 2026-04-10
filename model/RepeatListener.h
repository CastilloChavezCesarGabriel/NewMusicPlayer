#ifndef REPEAT_LISTENER_H
#define REPEAT_LISTENER_H

#include "IRepeatListener.h"
#include "ITrackListener.h"
#include "RepeatModeKind.h"

class RepeatListener final : public IRepeatListener {
private:
    IRepeatListener& repeats_;
    ITrackListener& tracks_;

public:
    RepeatListener(IRepeatListener& repeats, ITrackListener& tracks);
    void onRepeatChanged(RepeatModeKind kind) override;
    void stop() const;
};

#endif //REPEAT_LISTENER_H