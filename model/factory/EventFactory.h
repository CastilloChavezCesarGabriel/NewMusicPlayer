#ifndef EVENT_FACTORY_H
#define EVENT_FACTORY_H

#include "../event/TrackBus.h"
#include "../event/LibraryBus.h"
#include "../event/AdBus.h"
#include "../event/RepeatBus.h"

class EventFactory {
public:
    static TrackBus createTrackBus();
    static LibraryBus createLibraryBus();
    static AdBus createAdBus();
    static RepeatBus createRepeatBus();
};

#endif //EVENT_FACTORY_H