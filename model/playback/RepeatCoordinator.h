#ifndef REPEAT_COORDINATOR_H
#define REPEAT_COORDINATOR_H

#include "IRepeatListener.h"
#include "../event/ITrackListener.h"
#include "RepeatModeKind.h"

class RepeatCoordinator final : public IRepeatListener {
private:
    IRepeatListener& repeats_;
    ITrackListener& tracks_;

public:
    RepeatCoordinator(IRepeatListener& repeats, ITrackListener& tracks);
    void onChanged(RepeatModeKind kind) override;
    void stop() const;
};

#endif //REPEAT_COORDINATOR_H