#ifndef I_SEARCH_PROVIDER_H
#define I_SEARCH_PROVIDER_H

#include "../song/ISongVisitor.h"
#include <string>

class ISearchProvider {
public:
    virtual ~ISearchProvider() = default;
    virtual void search(const std::string& query, ISongVisitor& visitor) const = 0;
};

#endif //I_SEARCH_PROVIDER_H
