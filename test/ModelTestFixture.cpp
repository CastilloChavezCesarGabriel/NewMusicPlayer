#include "ModelTestFixture.h"
#include <filesystem>
#include <fstream>

void ModelTestFixture::SetUp() {
    base_directory_ = std::filesystem::temp_directory_path().string() + "/" + identify();
    music_directory_ = base_directory_ + "/music";
    ads_directory_ = base_directory_ + "/announcements";
    std::filesystem::create_directories(music_directory_);
    std::filesystem::create_directories(ads_directory_);
    track_bus_.add(listener_);
    library_bus_.add(listener_);
    ad_bus_.add(listener_);
    repeat_bus_.add(listener_);
}

void ModelTestFixture::TearDown() {
    std::filesystem::remove_all(base_directory_);
}

void ModelTestFixture::createSong(const std::string& name) const {
    std::ofstream(music_directory_ + "/" + name) << "audio";
}

void ModelTestFixture::createAd(const std::string& name) const {
    std::ofstream(ads_directory_ + "/" + name) << "ad";
}

void ModelTestFixture::build() {
    directory_ = std::make_unique<MusicDirectory>(music_directory_);
    tracklist_ = std::make_unique<Tracklist>();
    directory_->load(*tracklist_);
    cursor_ = std::make_unique<TrackCursor>(*tracklist_, track_bus_);

    ShuffleArrangement initial;
    tracklist_->arrange(initial);

    ad_policy_ = std::make_unique<RandomAdPolicy>(dice_);
    advertisement_ = std::make_unique<Advertisement>(*ad_policy_, ad_bus_, track_bus_);
    advertisement_->load(ads_directory_);

    repeat_listener_ = std::make_unique<RepeatCoordinator>(repeat_bus_, track_bus_);
    repeat_mode_ = std::make_unique<RepeatMode>(*cursor_, *repeat_listener_);

    playback_ = std::make_unique<PlaybackService>(*cursor_, *advertisement_, *repeat_mode_);
    library_ = std::make_unique<LibraryService>(*directory_, *tracklist_, library_bus_);
    setlist_ = std::make_unique<Setlist>(*tracklist_, *cursor_, library_bus_);
    catalog_ = std::make_unique<TrackCatalog>(*tracklist_);
    repeat_switch_ = std::make_unique<RepeatModeCommand>(*repeat_mode_);
}
