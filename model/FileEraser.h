#ifndef FILE_ERASER_H
#define FILE_ERASER_H

#include "IPathVisitor.h"
#include "MusicDirectory.h"

class FileEraser final : public IPathVisitor {
private:
    MusicDirectory& directory_;

public:
    explicit FileEraser(MusicDirectory& directory);
    void visit(const std::string& path) override;
};

#endif //FILE_ERASER_H