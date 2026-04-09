#ifndef PLAYBACK_H
#define PLAYBACK_H

#include "../Playlist.h"
#include "../Advertisement.h"
#include "../RepeatMode.h"
#include <string>

class Playback {
private:
    Playlist& playlist_;
    Advertisement& advertisement_;
    RepeatMode& repeat_mode_;

public:
    Playback(Playlist& playlist, Advertisement& advertisement, RepeatMode& repeat_mode);

    void play(int index);
    void pick(const std::string& name);
    void advance();
    void retreat();
    void end();
    void skip();
};

#endif //PLAYBACK_H