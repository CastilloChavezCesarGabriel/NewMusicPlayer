#ifndef SONG_VISITOR_SPY_H
#define SONG_VISITOR_SPY_H

#include "../model/song/ISongVisitor.h"
#include <string>
#include <vector>

class SongVisitorSpy final : public ISongVisitor {
private:
    std::vector<std::string> names_;
    std::vector<std::string> paths_;

public:
    void visit(const std::string& name, const std::string& path) override;

    void expectName(const std::string& name) const;
    void expectPath(const std::string& path) const;
    void expectEmpty() const;
    void expectNotEmpty() const;
    void expectCount(int expected) const;
    void expectNameAt(int index, const std::string& name) const;
};

#endif //SONG_VISITOR_SPY_H