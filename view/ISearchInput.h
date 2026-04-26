#ifndef I_SEARCH_INPUT_H
#define I_SEARCH_INPUT_H

#include <string>

class ISearchInput {
public:
    virtual ~ISearchInput() = default;
    virtual void onSearch(const std::string& query) = 0;
    virtual void onPick(const std::string& name) = 0;
};

#endif //I_SEARCH_INPUT_H