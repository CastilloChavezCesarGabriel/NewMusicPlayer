#include <filesystem>
#include "model/factory/EventFactory.h"
#include "model/factory/CollectionFactory.h"
#include "model/factory/PlaybackFactory.h"
#include "model/factory/ServiceFactory.h"
#include "controller/factory/ControllerFactory.h"
#include "controller/factory/RelayFactory.h"
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
    auto musicDirectory = CollectionFactory::createDirectory(base + "/resources/music");
    auto tracklist = CollectionFactory::createTracklist();
    musicDirectory.load(tracklist);
    auto trackCursor = CollectionFactory::createTrackCursor(tracklist, trackBus);
    auto initialShuffle = CollectionFactory::createShuffle();
    tracklist.arrange(initialShuffle);

    // Playback system
    auto dice = PlaybackFactory::createDice();
    auto adPolicy = PlaybackFactory::createAdPolicy(dice);
    auto advertisement = PlaybackFactory::createAdvertisement(*adPolicy, adBus, trackBus);
    advertisement->load(base + "/resources/announcements");
    auto repeatListener = PlaybackFactory::createRepeatCoordinator(repeatBus, trackBus);
    auto repeatMode = PlaybackFactory::createRepeatMode(*trackCursor, *repeatListener);

    // Services
    auto playback = ServiceFactory::createPlayback(*trackCursor, *advertisement, *repeatMode);
    auto library = ServiceFactory::createLibrary(musicDirectory, tracklist, libraryBus);
    auto setlist = ServiceFactory::createSetlist(tracklist, *trackCursor, libraryBus);
    auto catalog = ServiceFactory::createTrackCatalog(tracklist);
    auto repeatSwitch = ServiceFactory::createRepeatModeCommand(*repeatMode);

    // Layout shell (Created early to parent the notifications and dialogs)
    QtView view;

    // Passive widgets
    auto* audio = QtPlaybackFactory::createAudio();
    auto* sortHeader = QtDisplayFactory::createSortHeader();
    auto* searchOverlay = QtDisplayFactory::createSearchOverlay();
    auto* notification = QtDialogFactory::createNotification(&view);
    auto* dialog = QtDialogFactory::createDialog(&view);

    // Controllers
    auto transportController = ControllerFactory::createTransport(*playback, *audio, *searchOverlay);
    auto libraryController = ControllerFactory::createLibrary(*library, *dialog);
    auto arrangementController = ControllerFactory::createArrangement(*setlist, *repeatSwitch, *sortHeader);
    auto searchController = ControllerFactory::createSearch(*catalog, *playback, *searchOverlay);

    // Active widgets
    auto* display = QtDisplayFactory::createDisplay(*transportController, *libraryController);
    auto* transport = QtPlaybackFactory::createTransport(*transportController);
    auto* shuffleButton = QtArrangementFactory::createShuffleButton(*arrangementController);
    auto* repeatButton = QtArrangementFactory::createRepeatButton(*arrangementController);
    auto* volume = QtPlaybackFactory::createVolume(*transportController);
    auto* toolbar = QtDisplayFactory::createToolbar(*transportController, *libraryController);

    // Connections (cross-layer)
    QtSearchField searchField;
    QtEndConnection endConnection(*audio, *transportController);
    QtSearchFieldConnection searchFieldConnection(searchField, *searchController);
    QtPickConnection pickConnection(*searchOverlay, *searchController);
    QtClearConnection clearConnection(*searchOverlay, searchField);
    QtSortConnection sortConnection(*sortHeader, *arrangementController);

    // Connections (adapter-to-adapter)
    QtToggleConnection toggleConnection(*audio, *transport);
    QtRevealConnection revealConnection(*audio, *toolbar);
    QtRemoveConnection removeConnection(*toolbar, *display);

    // Enable broadcast
    EnableCoordinator enableCoordinator;
    enableCoordinator.add(*transport);
    enableCoordinator.add(*shuffleButton);
    enableCoordinator.add(*repeatButton);
    enableCoordinator.add(*toolbar);
    enableCoordinator.add(*audio);
    enableCoordinator.add(*display);
    enableCoordinator.add(*searchOverlay);

    // Relays
    auto trackRelay = RelayFactory::createTrackRelay(*audio, *display, enableCoordinator);
    auto libraryRelay = RelayFactory::createLibraryRelay(*catalog, *display, *notification);
    auto adRelay = RelayFactory::createAdRelay(enableCoordinator, *audio, *toolbar);
    auto repeatRelay = RelayFactory::createRepeatRelay(*repeatButton);

    trackBus.add(*trackRelay);
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
    view.place(*toolbar);
    view.attach(*searchOverlay);

    view.show();
    return app.exec();
}