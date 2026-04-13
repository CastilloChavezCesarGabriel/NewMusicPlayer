#ifndef I_REFRESHABLE_H
#define I_REFRESHABLE_H

class IRefreshable {
public:
    virtual ~IRefreshable() = default;
    virtual void refresh() = 0;
};

#endif //I_REFRESHABLE_H