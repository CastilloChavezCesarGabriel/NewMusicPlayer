#ifndef CONTROLLER_FACTORY_H
#define CONTROLLER_FACTORY_H

#include "../TransportController.h"
#include "../LibraryController.h"
#include "../OrderingController.h"
#include "../RepeatController.h"
#include "../SearchController.h"
#include <memory>

class ControllerFactory {
public:
    static std::unique_ptr<TransportController> createTransport(PlaybackTransport& playback, IAudioPlayer& audio, ISearchPanel& search);
    static std::unique_ptr<LibraryController> createLibrary(LibraryEditor& library, IDialog& dialog);
    static std::unique_ptr<OrderingController> createOrdering(Setlist& setlist, ISortDisplay& sort);
    static std::unique_ptr<RepeatController> createRepeat(RepeatPolicy& repeatPolicy);
    static std::unique_ptr<SearchController> createSearch(ISearchProvider& provider, PlaybackTransport& playback, ISearchPanel& search);
};

#endif //CONTROLLER_FACTORY_H