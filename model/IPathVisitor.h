#ifndef I_PATH_VISITOR_H
#define I_PATH_VISITOR_H
#include <string>

class IPathVisitor {
public:
    virtual ~IPathVisitor() = default;
    virtual void visit(const std::string& path) = 0;
};

#endif //I_PATH_VISITOR_H
