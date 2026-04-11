#include <filesystem>
#include "core/EventFactory.h"
#include "core/CollectionFactory.h"
#include "core/PlaybackFactory.h"
#include "core/ServiceFactory.h"
#include "core/ControllerFactory.h"
#include "core/RelayFactory.h"
#include "adapters/qt/QtView.h"
#include "adapters/qt/QtStyler.h"
#include "adapters/qt/QtViewFactory.h"
#include "adapters/qt/QtSearchField.h"
#include "adapters/qt/QtEndConnection.h"
#include "adapters/qt/QtToggleConnection.h"
#include "adapters/qt/QtRevealConnection.h"
#include "adapters/qt/QtSearchFieldConnection.h"
#include "adapters/qt/QtPickConnection.h"
#include "adapters/qt/QtClearConnection.h"
#include "adapters/qt/QtSortConnection.h"
#include "adapters/qt/QtRemoveConnection.h"
#include "controller/EnableGroup.h"

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
    auto cursor = CollectionFactory::createCursor(tracklist, trackBus);
    auto initialShuffle = CollectionFactory::createShuffle();
    tracklist.arrange(initialShuffle);

    // Playback system
    auto dice = PlaybackFactory::createDice();
    auto adPolicy = PlaybackFactory::createAdPolicy(dice);
    auto advertisement = PlaybackFactory::createAdvertisement(*adPolicy, adBus, trackBus);
    advertisement->load(base + "/resources/announcements");
    auto repeatListener = PlaybackFactory::createRepeatListener(repeatBus, trackBus);
    auto repeatMode = PlaybackFactory::createRepeatMode(*cursor, *repeatListener);

    // Services
    auto playback = ServiceFactory::createPlayback(*cursor, *advertisement, *repeatMode);
    auto library = ServiceFactory::createLibrary(musicDirectory, tracklist, libraryBus);
    auto setlist = ServiceFactory::createSetlist(tracklist, *cursor, libraryBus);
    auto catalog = ServiceFactory::createCatalog(tracklist);
    auto repeatSwitch = ServiceFactory::createRepeatSwitch(*repeatMode);

    // Layout shell (created early so it can parent notification/dialog)
    QtView view;

    // Passive widgets
    auto* audio = QtViewFactory::createAudio();
    auto* sortHeader = QtViewFactory::createSortHeader();
    auto* searchOverlay = QtViewFactory::createSearchOverlay();
    auto* notification = QtViewFactory::createNotification(&view);
    auto* dialog = QtViewFactory::createDialog(&view);

    // Controllers
    auto transportCtrl = ControllerFactory::createTransport(*playback, *audio, *searchOverlay);
    auto libraryCtrl = ControllerFactory::createLibrary(*library, *dialog);
    auto arrangementCtrl = ControllerFactory::createArrangement(*setlist, *repeatSwitch, *sortHeader);
    auto searchCtrl = ControllerFactory::createSearch(*catalog, *playback, *searchOverlay);

    // Active widgets
    auto* display = QtViewFactory::createDisplay(*transportCtrl, *libraryCtrl);
    QtSearchField searchField;
    auto* transport = QtViewFactory::createTransport(*transportCtrl);
    auto* arrangement = QtViewFactory::createArrangement(*arrangementCtrl);
    auto* volume = QtViewFactory::createVolume(*transportCtrl);
    auto* toolbar = QtViewFactory::createToolbar(*transportCtrl, *libraryCtrl);

    // Connections (cross-layer)
    QtEndConnection endConnection(*audio, *transportCtrl);
    QtSearchFieldConnection searchFieldConnection(searchField, *searchCtrl);
    QtPickConnection pickConnection(*searchOverlay, *searchCtrl);
    QtClearConnection clearConnection(*searchOverlay, searchField);
    QtSortConnection sortConnection(*sortHeader, *arrangementCtrl);

    // Connections (adapter-to-adapter)
    QtToggleConnection toggleConnection(*audio, *transport);
    QtRevealConnection revealConnection(*audio, *toolbar);
    QtRemoveConnection removeConnection(*toolbar, *display);

    // Enable broadcast
    EnableGroup enableGroup;
    enableGroup.add(*transport);
    enableGroup.add(*arrangement);
    enableGroup.add(*toolbar);
    enableGroup.add(*audio);

    // Relays
    auto trackRelay = RelayFactory::createTrackRelay(*audio, *display, enableGroup);
    auto libraryRelay = RelayFactory::createLibraryRelay(*catalog, *display, *notification);
    auto adRelay = RelayFactory::createAdRelay(enableGroup, *audio, *toolbar);
    auto repeatRelay = RelayFactory::createRepeatRelay(*arrangement);

    trackBus.add(*trackRelay);
    libraryBus.add(*libraryRelay);
    adBus.add(*adRelay);
    repeatBus.add(*repeatRelay);

    // Layout
    view.place(searchField);
    view.place(*sortHeader);
    view.place(*display);
    view.place(*audio);
    view.place(*transport);
    view.place(*arrangement);
    view.place(*volume);
    view.place(*toolbar);
    view.attach(*searchOverlay);

    view.show();
    return app.exec();
}