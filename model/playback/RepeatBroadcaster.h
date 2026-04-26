#ifndef REPEAT_BROADCASTER_H
#define REPEAT_BROADCASTER_H

#include "IRepeatListener.h"
#include "../event/ITrackListener.h"
#include "RepeatModeKind.h"

class RepeatBroadcaster final : public IRepeatListener {
private:
    IRepeatListener& repeats_;
    ITrackListener& tracks_;

public:
    RepeatBroadcaster(IRepeatListener& repeats, ITrackListener& tracks);
    void onChanged(RepeatModeKind kind) override;
    void stop() const;
};

#endif //REPEAT_BROADCASTER_H