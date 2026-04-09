#include "Advertisement.h"
#include "MusicLibrary.h"

Advertisement::Advertisement(const std::string& adsPath, IDice& dice, PlaybackNotifier& notifier)
    : path_(adsPath), dice_(dice), notifier_(notifier) {
}

void Advertisement::load() {
    ads_ = MusicLibrary::scan(path_);
}

bool Advertisement::isScheduled() const {
    return dice_.roll(100) <= 25;
}

int Advertisement::randomize() const {
    return (dice_.roll(6) + 4) * 1000;
}

bool Advertisement::interrupt() {
    if (ads_.empty() || !isScheduled()) return false;

    is_playing_ = true;
    notifier_.onEnabled(false);
    notifier_.onSchedule(randomize());

    const int index = dice_.roll(static_cast<int>(ads_.size())) - 1;
    notifier_.onStart(ads_.at(index));
    return true;
}

bool Advertisement::conclude() {
    if (!is_playing_) return false;
    is_playing_ = false;
    notifier_.onCancel();
    notifier_.onReveal(false);
    notifier_.onEnabled(true);
    return true;
}
