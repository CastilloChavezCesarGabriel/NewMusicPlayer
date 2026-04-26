#include "ControllerFactory.h"
#include "../TitleDescendingSort.h"
#include "../CustomMode.h"
#include "../../model/tracklist/QuickSort.h"
#include "../../model/tracklist/DurationSort.h"
#include "../../model/tracklist/DateSort.h"

std::unique_ptr<TransportController> ControllerFactory::createTransport(PlaybackService& playback, IAudioPlayer& audio, ISearchPanel& search) {
    return std::make_unique<TransportController>(playback, audio, search);
}

std::unique_ptr<LibraryController> ControllerFactory::createLibrary(LibraryService& library, IDialog& dialog) {
    return std::make_unique<LibraryController>(library, dialog);
}

std::unique_ptr<ArrangementController> ControllerFactory::createArrangement(Setlist& setlist, RepeatPolicy& repeatMode, ISortDisplay& sort) {
    auto controller = std::make_unique<ArrangementController>(setlist, repeatMode, sort);
    controller->add(std::make_unique<SortMode>("Title \xe2\x96\xb2", new QuickSort()));
    controller->add(std::make_unique<TitleDescendingSort>());
    controller->add(std::make_unique<SortMode>("Duration \xe2\x96\xb2", new DurationSort()));
    controller->add(std::make_unique<SortMode>("Date \xe2\x96\xb2", new DateSort()));
    controller->add(std::make_unique<CustomMode>());
    return controller;
}

std::unique_ptr<SearchController> ControllerFactory::createSearch(ISearchProvider& provider, PlaybackService& playback, ISearchPanel& search) {
    return std::make_unique<SearchController>(provider, playback, search);
}