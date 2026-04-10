#include "Advertisement.h"
#include "MusicDirectory.h"

Advertisement::Advertisement(IAdPolicy& policy, IAdListener& ads_events, ITrackListener& tracks)
    : policy_(policy), ads_events_(ads_events), tracks_(tracks) {
}

void Advertisement::load(const std::string& adsPath) {
    const MusicDirectory directory(adsPath);
    ads_ = directory.scan();
}

bool Advertisement::interrupt() {
    if (ads_.empty() || !policy_.decide()) return false;

    is_playing_ = true;
    ads_events_.onEnabled(false);
    ads_events_.onSchedule(policy_.clock());
    tracks_.onStart(ads_.at(policy_.pick(static_cast<int>(ads_.size()))));
    return true;
}

bool Advertisement::conclude() {
    if (!is_playing_) return false;
    is_playing_ = false;
    ads_events_.onCancel();
    ads_events_.onReveal(false);
    ads_events_.onEnabled(true);
    return true;
}
