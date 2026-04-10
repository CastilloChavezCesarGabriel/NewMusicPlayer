#include "AdRelay.h"

AdRelay::AdRelay(IEnableable& enable, ITimingPanel& timing, IToolbarDisplay& toolbar)
    : enable_(enable), timing_(timing), toolbar_(toolbar) {}

void AdRelay::onEnabled(const bool state) {
    enable_.enable(state);
}

void AdRelay::onSchedule(const int delay) {
    timing_.schedule(delay);
}

void AdRelay::onCancel() {
    timing_.cancel();
}

void AdRelay::onReveal(const bool visible) {
    toolbar_.reveal(visible);
}
