#ifndef CONTROLLER_FACTORY_H
#define CONTROLLER_FACTORY_H

#include "../controller/TransportController.h"
#include "../controller/LibraryController.h"
#include "../controller/ArrangementController.h"
#include "../controller/SearchController.h"
#include <memory>

class ControllerFactory {
public:
    static std::unique_ptr<TransportController> createTransport(Playback& playback, IAudioPlayer& audio, ISearchPanel& search);
    static std::unique_ptr<LibraryController> createLibrary(Library& library, IDialog& dialog);
    static std::unique_ptr<ArrangementController> createArrangement(Setlist& setlist, RepeatSwitch& repeat, ISortDisplay& sort);
    static std::unique_ptr<SearchController> createSearch(Catalog& catalog, Playback& playback, ISearchPanel& search);
};

#endif //CONTROLLER_FACTORY_H