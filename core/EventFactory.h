#ifndef EVENT_FACTORY_H
#define EVENT_FACTORY_H

#include "../model/TrackBus.h"
#include "../model/LibraryBus.h"
#include "../model/AdBus.h"
#include "../model/RepeatBus.h"

class EventFactory {
public:
    static TrackBus createTrackBus();
    static LibraryBus createLibraryBus();
    static AdBus createAdBus();
    static RepeatBus createRepeatBus();
};

#endif //EVENT_FACTORY_H
