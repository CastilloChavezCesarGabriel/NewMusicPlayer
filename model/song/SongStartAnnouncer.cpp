#include "SongStartAnnouncer.h"

SongStartAnnouncer::SongStartAnnouncer(ITrackListener& tracks)
    : tracks_(tracks) {
}

void SongStartAnnouncer::visit(const std::string& path) {
    tracks_.onStart(path);
}