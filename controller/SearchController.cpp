#include "SearchController.h"
#include "PlaylistPresenter.h"

SearchController::SearchController(ISearchProvider& provider, PlaybackTransport& playback, ISearchPanel& search)
    : provider_(provider), playback_(playback), search_(search) {}

void SearchController::onSearch(const std::string& query) {
    if (query.empty()) {
        search_.dismiss();
        return;
    }
    PlaylistPresenter renderer;
    provider_.search(query, renderer);
    renderer.suggest(search_);
}

void SearchController::onPick(const std::string& name) {
    playback_.pick(name);
    search_.dismiss();
}