#ifndef I_ORDER_CONTROL_H
#define I_ORDER_CONTROL_H

class IOrderControl {
public:
    virtual ~IOrderControl() = default;
    virtual void onSort() = 0;
    virtual void onShuffle() = 0;
};

#endif //I_ORDER_CONTROL_H