#include "PlaylistPresenter.h"

void PlaylistPresenter::visit(const std::string& name, const std::string&) {
    names_.push_back(name);
}

void PlaylistPresenter::render(IPlaylistPanel& panel) const {
    panel.refresh(names_);
}

void PlaylistPresenter::suggest(ISearchPanel& search) const {
    search.suggest(names_);
}