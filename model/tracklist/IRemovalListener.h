#ifndef I_REMOVAL_LISTENER_H
#define I_REMOVAL_LISTENER_H

class IRemovalListener {
public:
    virtual ~IRemovalListener() = default;
    virtual void onRemoved(int index) = 0;
};

#endif //I_REMOVAL_LISTENER_H