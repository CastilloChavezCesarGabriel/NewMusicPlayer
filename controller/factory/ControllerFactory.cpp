#include "ControllerFactory.h"
#include "../TitleDescendingSort.h"
#include "../CustomMode.h"
#include "../../model/tracklist/QuickSort.h"
#include "../../model/tracklist/DurationSort.h"
#include "../../model/tracklist/DateSort.h"

std::unique_ptr<TransportController> ControllerFactory::createTransport(PlaybackTransport& playback, IAudioPlayer& audio, ISearchPanel& search) {
    return std::make_unique<TransportController>(playback, audio, search);
}

std::unique_ptr<LibraryController> ControllerFactory::createLibrary(LibraryEditor& library, IDialog& dialog) {
    return std::make_unique<LibraryController>(library, dialog);
}

std::unique_ptr<PlaybackModeController> ControllerFactory::createPlaybackMode(Setlist& setlist, RepeatPolicy& repeatPolicy, ISortDisplay& sort) {
    auto controller = std::make_unique<PlaybackModeController>(setlist, repeatPolicy, sort);
    controller->add(std::make_unique<SortMode>("Title \xe2\x96\xb2", std::make_unique<QuickSort>()));
    controller->add(std::make_unique<TitleDescendingSort>());
    controller->add(std::make_unique<SortMode>("Duration \xe2\x96\xb2", std::make_unique<DurationSort>()));
    controller->add(std::make_unique<SortMode>("Date \xe2\x96\xb2", std::make_unique<DateSort>()));
    controller->add(std::make_unique<CustomMode>());
    return controller;
}

std::unique_ptr<SearchController> ControllerFactory::createSearch(ISearchProvider& provider, PlaybackTransport& playback, ISearchPanel& search) {
    return std::make_unique<SearchController>(provider, playback, search);
}