#ifndef ADVERTISEMENT_H
#define ADVERTISEMENT_H

#include "IAdListener.h"
#include "../event/ITrackListener.h"
#include "IAdPolicy.h"
#include <string>
#include <vector>

class Advertisement {
private:
    std::vector<std::string> ads_;
    IAdPolicy& policy_;
    IAdListener& ads_events_;
    ITrackListener& tracks_;
    bool is_playing_ = false;

public:
    Advertisement(IAdPolicy& policy, IAdListener& adsEvents, ITrackListener& tracks);

    void load(const std::string& adsPath);
    bool interrupt();
    bool conclude();
};

#endif //ADVERTISEMENT_H