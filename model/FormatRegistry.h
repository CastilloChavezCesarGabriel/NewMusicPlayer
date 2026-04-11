#ifndef FORMAT_REGISTRY_H
#define FORMAT_REGISTRY_H

#include <set>
#include <string>

class FormatRegistry final {
private:
    std::set<std::string> extensions_;

public:
    FormatRegistry();
    bool supports(const std::string& filename) const;
};

#endif //FORMAT_REGISTRY_H