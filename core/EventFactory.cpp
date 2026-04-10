#include "EventFactory.h"

TrackBus EventFactory::createTrackBus() {
    return TrackBus();
}

LibraryBus EventFactory::createLibraryBus() {
    return LibraryBus();
}

AdBus EventFactory::createAdBus() {
    return AdBus();
}

RepeatBus EventFactory::createRepeatBus() {
    return RepeatBus();
}
