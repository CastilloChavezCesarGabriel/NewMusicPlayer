#ifndef PLAYBACK_H
#define PLAYBACK_H

#include "../Cursor.h"
#include "../Advertisement.h"
#include "../RepeatMode.h"
#include <string>

class Playback {
private:
    Cursor& cursor_;
    Advertisement& advertisement_;
    RepeatMode& repeat_mode_;

    void start() const;

public:
    Playback(Cursor& cursor, Advertisement& advertisement, RepeatMode& repeat_mode);

    void play(int index) const;
    void pick(const std::string& name) const;
    void advance() const;
    void retreat() const;
    void end() const;
    void skip() const;
};

#endif //PLAYBACK_H