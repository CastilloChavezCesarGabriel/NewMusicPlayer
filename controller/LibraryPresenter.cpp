#include "LibraryPresenter.h"
#include "PlaylistPresenter.h"

LibraryPresenter::LibraryPresenter(TrackCatalog& catalog, IPlaylistPanel& panel, INotification& notification)
    : catalog_(catalog), panel_(panel), notification_(notification) {
    onChanged();
}

void LibraryPresenter::onChanged() {
    PlaylistPresenter renderer;
    catalog_.accept(renderer);
    renderer.render(panel_);
}

void LibraryPresenter::onFeedback(const std::string& message, const bool success) {
    notification_.notify(message, success);
}