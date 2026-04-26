#ifndef AD_SCHEDULER_H
#define AD_SCHEDULER_H

#include "IAdListener.h"
#include "../event/ITrackListener.h"
#include "IAdPolicy.h"
#include <string>
#include <vector>

class AdScheduler {
private:
    std::vector<std::string> ads_;
    IAdPolicy& policy_;
    IAdListener& ads_events_;
    ITrackListener& tracks_;
    bool is_playing_ = false;

public:
    AdScheduler(IAdPolicy& policy, IAdListener& adsEvents, ITrackListener& tracks);

    void load(const std::string& adsPath);
    bool interrupt();
    bool conclude();
};

#endif //AD_SCHEDULER_H