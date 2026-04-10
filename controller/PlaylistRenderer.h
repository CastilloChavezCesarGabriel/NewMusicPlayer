#ifndef PLAYLIST_RENDERER_H
#define PLAYLIST_RENDERER_H

#include "../model/ISongVisitor.h"
#include "../view/IPlaylistPanel.h"
#include "../view/ISearchPanel.h"
#include <vector>
#include <string>

class PlaylistRenderer final : public ISongVisitor {
private:
    std::vector<std::string> names_;

public:
    void visit(const std::string& name, const std::string& path) override;
    void render(IPlaylistPanel& panel) const;
    void suggest(ISearchPanel& search) const;
};

#endif //PLAYLIST_RENDERER_H