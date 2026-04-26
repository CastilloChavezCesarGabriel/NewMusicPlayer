#include "AdPresenter.h"

AdPresenter::AdPresenter(IEnableable& enable, ITimingPanel& timing, IToolbarDisplay& toolbar)
    : enable_(enable), timing_(timing), toolbar_(toolbar) {}

void AdPresenter::onEnable(const bool state) {
    enable_.enable(state);
}

void AdPresenter::onSchedule(const int delay) {
    timing_.schedule(delay);
}

void AdPresenter::onCancel() {
    timing_.cancel();
}

void AdPresenter::onReveal(const bool visible) {
    toolbar_.reveal(visible);
}