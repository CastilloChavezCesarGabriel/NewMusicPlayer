#ifndef I_LIBRARY_LISTENER_H
#define I_LIBRARY_LISTENER_H
#include <string>

class ILibraryListener {
public:
    virtual ~ILibraryListener() = default;
    virtual void onChanged() = 0;
    virtual void onFeedback(const std::string& message, bool success) = 0;
};

#endif //I_LIBRARY_LISTENER_H