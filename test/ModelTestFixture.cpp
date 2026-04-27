#include "ModelTestFixture.h"
#include "../model/tracklist/TracklistImporter.h"
#include "../model/tracklist/ShuffleStrategy.h"
#include "../model/playback/NoRepeatStrategy.h"
#include "../model/playback/RepeatOneStrategy.h"
#include "../model/playback/RepeatAllStrategy.h"
#include <filesystem>
#include <fstream>

void ModelTestFixture::SetUp() {
    base_directory_ = std::filesystem::temp_directory_path().string() + "/" + identify();
    music_directory_ = base_directory_ + "/music";
    ads_directory_ = base_directory_ + "/announcements";
    std::filesystem::create_directories(music_directory_);
    std::filesystem::create_directories(ads_directory_);
    track_bus_.add(track_spy_);
    library_bus_.add(library_spy_);
    ad_bus_.add(ad_spy_);
}

void ModelTestFixture::TearDown() {
    std::filesystem::remove_all(base_directory_);
}

std::string ModelTestFixture::prepare(const std::string& name) const {
    const std::string src_directory = base_directory_ + "/src";
    std::filesystem::create_directories(src_directory);
    const std::string path = src_directory + "/" + name;
    std::ofstream(path) << "audio";
    return path;
}

void ModelTestFixture::createSong(const std::string& name) const {
    std::ofstream(music_directory_ + "/" + name) << "audio";
}

void ModelTestFixture::build() {
    directory_ = std::make_unique<MusicDirectory>(music_directory_);
    tracklist_ = std::make_unique<Tracklist>();
    TracklistImporter importer(*tracklist_);
    directory_->load(importer);
    cursor_ = std::make_unique<TrackCursor>(*tracklist_, track_bus_);

    ShuffleStrategy initial;
    tracklist_->reorder(initial);

    ad_policy_ = std::make_unique<RandomAdPolicy>(dice_);
    ad_scheduler_ = std::make_unique<AdScheduler>(*ad_policy_, ad_bus_, track_bus_);
    ad_scheduler_->load(ads_directory_);

    repeat_listener_ = std::make_unique<RepeatBroadcaster>(repeat_bus_, track_bus_);
    repeat_policy_ = std::make_unique<RepeatPolicy>(*cursor_, *repeat_listener_);
    repeat_policy_->add(std::make_unique<NoRepeatStrategy>());
    repeat_policy_->add(std::make_unique<RepeatOneStrategy>());
    repeat_policy_->add(std::make_unique<RepeatAllStrategy>());

    playback_ = std::make_unique<PlaybackTransport>(*cursor_, *ad_scheduler_, *repeat_policy_);
    library_ = std::make_unique<LibraryEditor>(*directory_, *tracklist_, library_bus_);
    setlist_ = std::make_unique<Setlist>(*tracklist_, *cursor_, library_bus_);
    catalog_ = std::make_unique<TrackCatalog>(*tracklist_);
}