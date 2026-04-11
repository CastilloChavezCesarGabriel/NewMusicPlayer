#include "ControllerFactory.h"

std::unique_ptr<TransportController> ControllerFactory::createTransport(Playback& playback, IAudioPlayer& audio, ISearchPanel& search) {
    return std::make_unique<TransportController>(playback, audio, search);
}

std::unique_ptr<LibraryController> ControllerFactory::createLibrary(Library& library, IDialog& dialog) {
    return std::make_unique<LibraryController>(library, dialog);
}

std::unique_ptr<ArrangementController> ControllerFactory::createArrangement(Setlist& setlist, RepeatSwitch& repeat, ISortDisplay& sort) {
    return std::make_unique<ArrangementController>(setlist, repeat, sort);
}

std::unique_ptr<SearchController> ControllerFactory::createSearch(Catalog& catalog, Playback& playback, ISearchPanel& search) {
    return std::make_unique<SearchController>(catalog, playback, search);
}