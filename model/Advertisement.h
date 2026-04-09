#ifndef ADVERTISEMENT_H
#define ADVERTISEMENT_H

#include "PlaybackNotifier.h"
#include "IDice.h"
#include <string>
#include <vector>

class Advertisement {
private:
    std::vector<std::string> ads_;
    std::string path_;
    IDice& dice_;
    PlaybackNotifier& notifier_;
    bool is_playing_ = false;

    bool isScheduled() const;
    int randomize() const;

public:
    Advertisement(const std::string& adsPath, IDice& dice, PlaybackNotifier& notifier);

    void load();
    bool interrupt();
    bool conclude();
};

#endif //ADVERTISEMENT_H