#include "TracklistImporter.h"

TracklistImporter::TracklistImporter(Tracklist& tracklist) : tracklist_(tracklist) {}

void TracklistImporter::visit(const std::string& name, const std::string& path) {
    tracklist_.add(Song(name, path));
}