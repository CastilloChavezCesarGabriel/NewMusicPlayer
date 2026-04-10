#ifndef I_SONG_VISITOR_H
#define I_SONG_VISITOR_H

#include <string>

class ISongVisitor {
public:
    virtual ~ISongVisitor() = default;
    virtual void visit(const std::string& name, const std::string& path) = 0;
};

#endif //I_SONG_VISITOR_H