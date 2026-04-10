#include "LibraryRelay.h"
#include "PlaylistRenderer.h"

LibraryRelay::LibraryRelay(Catalog& catalog, IPlaylistPanel& panel, INotification& notification)
    : catalog_(catalog), panel_(panel), notification_(notification) {}

void LibraryRelay::onChanged() {
    PlaylistRenderer renderer;
    catalog_.accept(renderer);
    renderer.render(panel_);
}

void LibraryRelay::onFeedback(const std::string& message, const bool success) {
    notification_.notify(message, success);
}