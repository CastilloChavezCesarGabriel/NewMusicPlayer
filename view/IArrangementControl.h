#ifndef I_ARRANGEMENT_CONTROL_H
#define I_ARRANGEMENT_CONTROL_H

class IArrangementControl {
public:
    virtual ~IArrangementControl() = default;
    virtual void onSort() = 0;
    virtual void onShuffle() = 0;
    virtual void onRepeat() = 0;
};

#endif //I_ARRANGEMENT_CONTROL_H