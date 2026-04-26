#ifndef CONTROLLER_FACTORY_H
#define CONTROLLER_FACTORY_H

#include "../TransportController.h"
#include "../LibraryController.h"
#include "../PlaybackModeController.h"
#include "../SearchController.h"
#include <memory>

class ControllerFactory {
public:
    static std::unique_ptr<TransportController> createTransport(PlaybackTransport& playback, IAudioPlayer& audio, ISearchPanel& search);
    static std::unique_ptr<LibraryController> createLibrary(LibraryEditor& library, IDialog& dialog);
    static std::unique_ptr<PlaybackModeController> createPlaybackMode(Setlist& setlist, RepeatPolicy& repeatMode, ISortDisplay& sort);
    static std::unique_ptr<SearchController> createSearch(ISearchProvider& provider, PlaybackTransport& playback, ISearchPanel& search);
};

#endif //CONTROLLER_FACTORY_H
