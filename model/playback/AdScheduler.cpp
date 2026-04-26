#include "AdScheduler.h"
#include "../library/MusicDirectory.h"

AdScheduler::AdScheduler(IAdPolicy& policy, IAdListener& adsEvents, ITrackListener& tracks)
    : policy_(policy), ads_events_(adsEvents), tracks_(tracks) {
}

void AdScheduler::load(const std::string& adsPath) {
    const MusicDirectory directory(adsPath);
    ads_ = directory.scan();
}

bool AdScheduler::interrupt() {
    if (ads_.empty() || !policy_.decide()) return false;

    is_playing_ = true;
    ads_events_.onEnable(false);
    ads_events_.onSchedule(policy_.clock());
    tracks_.onStart(ads_.at(policy_.pick(static_cast<int>(ads_.size()))));
    return true;
}

bool AdScheduler::conclude() {
    if (!is_playing_) return false;
    is_playing_ = false;
    ads_events_.onCancel();
    ads_events_.onReveal(false);
    ads_events_.onEnable(true);
    return true;
}