#ifndef BUS_H
#define BUS_H

#include <vector>
#include <functional>

template<typename Listener>
class Bus {
private:
    std::vector<Listener*> listeners_;

protected:
    void broadcast(const std::function<void(Listener&)>& action) const {
        for (auto* listener : listeners_) {
            action(*listener);
        }
    }

public:
    virtual ~Bus() = default;

    void add(Listener& listener) {
        listeners_.push_back(&listener);
    }
};

#endif //BUS_H