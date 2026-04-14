#include "SearchController.h"
#include "PlaylistRenderer.h"

SearchController::SearchController(ISearchProvider& provider, PlaybackService& playback, ISearchPanel& search)
    : provider_(provider), playback_(playback), search_(search) {}

void SearchController::onSearch(const std::string& query) {
    if (query.empty()) {
        search_.dismiss();
        return;
    }
    PlaylistRenderer renderer;
    provider_.search(query, renderer);
    renderer.suggest(search_);
}

void SearchController::onPick(const std::string& name) {
    playback_.pick(name);
    search_.dismiss();
}