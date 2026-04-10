#include "PlaylistRenderer.h"

void PlaylistRenderer::visit(const std::string& name, const std::string&) {
    names_.push_back(name);
}

void PlaylistRenderer::render(IPlaylistPanel& panel) const {
    panel.refresh(names_);
}

void PlaylistRenderer::suggest(ISearchPanel& search) const {
    search.suggest(names_);
}