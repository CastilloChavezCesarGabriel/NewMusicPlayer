#include <filesystem>
#include "model/factory/EventFactory.h"
#include "model/factory/CollectionFactory.h"
#include "model/factory/PlaybackFactory.h"
#include "model/factory/ServiceFactory.h"
#include "controller/factory/ControllerFactory.h"
#include "controller/factory/PresenterFactory.h"
#include "adapters/qt/QtView.h"
#include "adapters/qt/style/QtStyler.h"
#include "adapters/qt/factory/QtPlaybackFactory.h"
#include "adapters/qt/factory/QtArrangementFactory.h"
#include "adapters/qt/factory/QtDisplayFactory.h"
#include "adapters/qt/factory/QtDialogFactory.h"
#include "adapters/qt/widget/QtSearchField.h"
#include "adapters/qt/connection/QtEndConnection.h"
#include "adapters/qt/connection/QtToggleConnection.h"
#include "adapters/qt/connection/QtRevealConnection.h"
#include "adapters/qt/connection/QtSearchFieldConnection.h"
#include "adapters/qt/connection/QtPickConnection.h"
#include "adapters/qt/connection/QtClearConnection.h"
#include "adapters/qt/connection/QtSortConnection.h"
#include "adapters/qt/connection/QtRemoveConnection.h"
#include "controller/EnableCoordinator.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const std::string base = std::filesystem::current_path().string();
    QtStyler::apply(app, base + "/resources/styles.qss");

    // Event buses
    auto trackBus = EventFactory::createTrackBus();
    auto libraryBus = EventFactory::createLibraryBus();
    auto adBus = EventFactory::createAdBus();
    auto repeatBus = EventFactory::createRepeatBus();

    // Music collection
    auto musicDirectory = CollectionFactory::createMusicDirectory(base + "/resources/music");
    auto tracklist = CollectionFactory::createTracklist();
    musicDirectory.load(tracklist);
    auto trackCursor = CollectionFactory::createTrackCursor(tracklist, trackBus);
    auto initialShuffle = CollectionFactory::createShuffleStrategy();
    tracklist.reorder(initialShuffle);

    // Playback system
    auto dice = PlaybackFactory::createDice();
    auto adPolicy = PlaybackFactory::createAdPolicy(dice);
    auto adScheduler = PlaybackFactory::createAdScheduler(*adPolicy, adBus, trackBus);
    adScheduler->load(base + "/resources/announcements");
    auto repeatListener = PlaybackFactory::createRepeatBroadcaster(repeatBus, trackBus);
    auto repeatPolicy = PlaybackFactory::createRepeatPolicy(*trackCursor, *repeatListener);

    // Services
    auto playback = ServiceFactory::createPlayback(*trackCursor, *adScheduler, *repeatPolicy);
    auto library = ServiceFactory::createLibrary(musicDirectory, tracklist, libraryBus);
    auto setlist = ServiceFactory::createSetlist(tracklist, *trackCursor, libraryBus);
    auto catalog = ServiceFactory::createTrackCatalog(tracklist);

    // Layout shell (Created early to parent the notifications and dialogs)
    QtView view;

    // Passive widgets
    auto* audio = QtPlaybackFactory::createAudio();
    auto* adTimer = QtPlaybackFactory::createAdTimer(&view);
    auto* sortHeader = QtDisplayFactory::createSortHeader();
    auto* searchOverlay = QtDisplayFactory::createSearchOverlay();
    auto* notification = QtDialogFactory::createNotification(&view);
    auto* dialog = QtDialogFactory::createDialog(&view);

    // Controllers
    auto transportController = ControllerFactory::createTransport(*playback, *audio, *searchOverlay);
    auto libraryController = ControllerFactory::createLibrary(*library, *dialog);
    auto playbackModeController = ControllerFactory::createPlaybackMode(*setlist, *repeatPolicy, *sortHeader);
    auto searchController = ControllerFactory::createSearch(*catalog, *playback, *searchOverlay);

    // Active widgets
    auto* display = QtDisplayFactory::createDisplay(*transportController, *libraryController);
    auto* transport = QtPlaybackFactory::createTransport(*transportController);
    auto* shuffleButton = QtArrangementFactory::createShuffleButton(*playbackModeController);
    auto* repeatButton = QtArrangementFactory::createRepeatButton(*playbackModeController);
    auto* volume = QtPlaybackFactory::createVolume(*transportController);
    auto* libraryBar = QtDisplayFactory::createLibraryBar(*libraryController);
    auto* skipButton = QtPlaybackFactory::createSkipButton(*transportController);

    // Connections (cross-layer)
    QtSearchField searchField;
    QtEndConnection endConnection(*audio, *transportController);
    QtSearchFieldConnection searchFieldConnection(searchField, *searchController);
    QtPickConnection pickConnection(*searchOverlay, *searchController);
    QtClearConnection clearConnection(*searchOverlay, searchField);
    QtSortConnection sortConnection(*sortHeader, *playbackModeController);

    // Connections (adapter-to-adapter)
    QtToggleConnection toggleConnection(*audio, *transport);
    QtRevealConnection revealConnection(*adTimer, *skipButton);
    QtRemoveConnection removeConnection(*libraryBar, *display);

    // Enable broadcast
    EnableCoordinator playbackControls;
    playbackControls.add(*transport);
    playbackControls.add(*shuffleButton);
    playbackControls.add(*repeatButton);
    playbackControls.add(*audio);

    EnableCoordinator adControls;
    adControls.add(playbackControls);
    adControls.add(*libraryBar);
    adControls.add(*display);
    adControls.add(*searchOverlay);

    // Relays
    auto trackRelay = PresenterFactory::createTrackPresenter(*audio, *display, playbackControls);
    auto arrangementRelay = PresenterFactory::createArrangementPresenter(*playbackModeController);
    auto libraryRelay = PresenterFactory::createLibraryPresenter(*catalog, *display, *notification);
    auto adRelay = PresenterFactory::createAdPresenter(adControls, *adTimer, *skipButton);
    auto repeatRelay = PresenterFactory::createRepeatPresenter(*repeatButton);

    trackBus.add(*trackRelay);
    libraryBus.add(*arrangementRelay);
    libraryBus.add(*libraryRelay);
    adBus.add(*adRelay);
    repeatBus.add(*repeatRelay);

    // Layout
    view.place(searchField);
    view.place(*sortHeader);
    view.place(*display);
    view.place(*audio);
    view.align(*shuffleButton, *transport, *repeatButton);
    view.place(*volume);
    view.place(*libraryBar);
    view.place(*skipButton);
    view.attach(*searchOverlay);

    view.show();
    return app.exec();
}