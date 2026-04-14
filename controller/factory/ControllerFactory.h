#ifndef CONTROLLER_FACTORY_H
#define CONTROLLER_FACTORY_H

#include "../TransportController.h"
#include "../LibraryController.h"
#include "../ArrangementController.h"
#include "../SearchController.h"
#include <memory>

class ControllerFactory {
public:
    static std::unique_ptr<TransportController> createTransport(PlaybackService& playback, IAudioPlayer& audio, ISearchPanel& search);
    static std::unique_ptr<LibraryController> createLibrary(LibraryService& library, IDialog& dialog);
    static std::unique_ptr<ArrangementController> createArrangement(Setlist& setlist, RepeatModeCommand& repeat, ISortDisplay& sort);
    static std::unique_ptr<SearchController> createSearch(ISearchProvider& provider, PlaybackService& playback, ISearchPanel& search);
};

#endif //CONTROLLER_FACTORY_H