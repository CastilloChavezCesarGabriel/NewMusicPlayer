#ifndef PATH_VISITOR_SPY_H
#define PATH_VISITOR_SPY_H

#include "../model/song/IPathVisitor.h"
#include <string>
#include <vector>

class PathVisitorSpy final : public IPathVisitor {
private:
    std::vector<std::string> paths_;

public:
    void visit(const std::string& path) override;

    void expectPath(const std::string& path) const;
};

#endif //PATH_VISITOR_SPY_H