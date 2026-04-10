#include "SearchController.h"
#include "PlaylistRenderer.h"

SearchController::SearchController(Catalog& catalog, Playback& playback, ISearchPanel& search)
    : catalog_(catalog), playback_(playback), search_(search) {}

void SearchController::onSearch(const std::string& query) {
    if (query.empty()) {
        search_.dismiss();
        return;
    }
    PlaylistRenderer renderer;
    catalog_.search(query, renderer);
    renderer.suggest(search_);
}

void SearchController::onPick(const std::string& name) {
    playback_.pick(name);
    search_.dismiss();
}