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
#include "controller/TrackRelay.h"
#include "controller/LibraryRelay.h"
#include "controller/AdRelay.h"
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

    QtView view;

    TrackRelay trackRelay(view, view, view);
    LibraryRelay libraryRelay(catalog, view, view);
    AdRelay adRelay(view);

    trackBus.add(trackRelay);
    libraryBus.add(libraryRelay);
    adBus.add(adRelay);
    repeatBus.add(adRelay);

    TransportController transport(playback, view, view);
    LibraryController libraryController(library, view);
    ArrangementController arrangement(setlist, repeatSwitch, view);
    SearchController searchController(catalog, playback, view);

    view.wire(transport, arrangement, libraryController, searchController);

    view.show();
    return app.exec();
}
