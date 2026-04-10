#include <filesystem>
#include "model/Tracklist.h"
#include "model/TracklistSink.h"
#include "model/Cursor.h"
#include "model/MusicDirectory.h"
#include "model/Advertisement.h"
#include "model/TrackBus.h"
#include "model/LibraryBus.h"
#include "model/AdBus.h"
#include "model/RepeatBus.h"
#include "model/RepeatListener.h"
#include "model/RepeatMode.h"
#include "model/Dice.h"
#include "model/RandomAdPolicy.h"
#include "model/ShuffleArrangement.h"
#include "model/service/Playback.h"
#include "model/service/Library.h"
#include "model/service/Setlist.h"
#include "model/service/Catalog.h"
#include "model/service/RepeatSwitch.h"
#include "adapters/qt/QtView.h"
#include "adapters/qt/QtStyler.h"
#include "adapters/qt/QtAudioEngine.h"
#include "adapters/qt/QtPlaylistDisplay.h"
#include "adapters/qt/QtSortHeader.h"
#include "adapters/qt/QtSearchOverlay.h"
#include "adapters/qt/QtNotification.h"
#include "adapters/qt/QtDialog.h"
#include "adapters/qt/QtTransportPanel.h"
#include "adapters/qt/QtArrangementPanel.h"
#include "adapters/qt/QtVolumePanel.h"
#include "adapters/qt/QtToolbar.h"
#include "controller/TrackRelay.h"
#include "controller/LibraryRelay.h"
#include "controller/AdRelay.h"
#include "controller/RepeatRelay.h"
#include "controller/EnableGroup.h"
#include "controller/TransportController.h"
#include "controller/LibraryController.h"
#include "controller/ArrangementController.h"
#include "controller/SearchController.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const std::string base = std::filesystem::current_path().string();
    QtStyler::apply(app, base + "/resources/styles.qss");

    Dice dice;
    TrackBus trackBus;
    LibraryBus libraryBus;
    AdBus adBus;
    RepeatBus repeatBus;

    MusicDirectory musicDirectory(base + "/resources/music");
    Tracklist tracklist;
    TracklistSink sink(tracklist);
    musicDirectory.load(sink);

    Cursor cursor(tracklist, trackBus);

    ShuffleArrangement initialShuffle;
    tracklist.arrange(initialShuffle);

    RandomAdPolicy adPolicy(dice);
    Advertisement advertisement(adPolicy, adBus, trackBus);
    advertisement.load(base + "/resources/announcements");

    RepeatListener repeatListener(repeatBus, trackBus);
    RepeatMode repeatMode(cursor, repeatListener);

    Playback playback(cursor, advertisement, repeatMode);
    Library library(musicDirectory, tracklist, libraryBus);
    Setlist setlist(tracklist, cursor, libraryBus);
    Catalog catalog(tracklist);
    RepeatSwitch repeatSwitch(repeatMode);

    // Adapter widgets
    QtAudioEngine audio;
    QtPlaylistDisplay display;
    QtSortHeader sortHeader;
    QtSearchOverlay searchOverlay;
    QtNotification notification(nullptr);
    QtDialog dialog(nullptr);

    // Controllers
    TransportController transportController(playback, audio, searchOverlay);
    LibraryController libraryController(library, dialog);
    ArrangementController arrangementController(setlist, repeatSwitch, sortHeader);
    SearchController searchController(catalog, playback, searchOverlay);

    // Panels that need controller refs
    QtTransportPanel transport(transportController);
    QtArrangementPanel arrangement(arrangementController);
    QtVolumePanel volume(transportController);
    QtToolbar toolbar;

    // Wire internal adapter signals
    audio.wire(transportController, transport, toolbar);
    display.wire(transportController, libraryController);
    searchOverlay.wire(searchController);
    sortHeader.wire(arrangementController);
    toolbar.wire(transportController, libraryController, display);

    // Enable broadcast
    EnableGroup enableGroup;
    enableGroup.add(transport);
    enableGroup.add(toolbar);
    enableGroup.add(audio);

    // Relays
    TrackRelay trackRelay(audio, display, enableGroup);
    LibraryRelay libraryRelay(catalog, display, notification);
    AdRelay adRelay(enableGroup, audio, toolbar);
    RepeatRelay repeatRelay(arrangement);

    trackBus.add(trackRelay);
    libraryBus.add(libraryRelay);
    adBus.add(adRelay);
    repeatBus.add(repeatRelay);

    // Layout
    QtView view;
    view.place(sortHeader);
    view.place(display);
    view.place(audio);
    view.place(transport);
    view.place(arrangement);
    view.place(volume);
    view.place(toolbar);
    view.wire(libraryController, searchController);

    view.show();
    return app.exec();
}