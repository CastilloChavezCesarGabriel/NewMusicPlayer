#include "TracklistSink.h"
#include "Song.h"

TracklistSink::TracklistSink(Tracklist& tracklist) : tracklist_(tracklist) {}

void TracklistSink::visit(const std::string& name, const std::string& path) {
    tracklist_.add(Song(name, path));
}