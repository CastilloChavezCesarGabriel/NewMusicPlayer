#include "SearchController.h"
#include "PlaylistRenderer.h"

SearchController::SearchController(Catalog& catalog, IPlayerView& view)
    : catalog_(catalog), view_(view) {}

void SearchController::search(const std::string& query) const {
    if (query.empty()) {
        view_.dismiss();
        return;
    }
    PlaylistRenderer renderer(view_);
    catalog_.search(query, renderer);
    renderer.suggest();
}
