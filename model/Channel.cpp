#include "Channel.h"

Channel::Channel(ITrackListener& tracks)
    : tracks_(tracks) {
}

void Channel::visit(const std::string& path) {
    tracks_.onStart(path);
}
