#ifndef I_TRACK_LISTENER_H
#define I_TRACK_LISTENER_H
#include <string>

class ITrackListener {
public:
    virtual ~ITrackListener() = default;
    virtual void onStart(const std::string& path) = 0;
    virtual void onSelected(int index) = 0;
    virtual void onStopped() = 0;
};

#endif //I_TRACK_LISTENER_H