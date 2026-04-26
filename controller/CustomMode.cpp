#include "CustomMode.h"

CustomMode::CustomMode() : SortMode("Custom", nullptr) {}

void CustomMode::apply(Setlist& setlist) {
    setlist.restore();
}