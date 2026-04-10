#ifndef PLAYLIST_RENDERER_H
#define PLAYLIST_RENDERER_H

#include "../model/ISongVisitor.h"
#include "../view/IPlayerView.h"
#include <vector>
#include <string>

class PlaylistRenderer final : public ISongVisitor {
private:
    IPlayerView& view_;
    std::vector<std::string> names_;

public:
    explicit PlaylistRenderer(IPlayerView& view);
    void visit(const std::string& name, const std::string& path) override;
    void render() const;
    void suggest() const;
};

#endif //PLAYLIST_RENDERER_H