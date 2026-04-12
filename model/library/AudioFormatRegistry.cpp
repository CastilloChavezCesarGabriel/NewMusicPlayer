#include "AudioFormatRegistry.h"
#include <filesystem>

AudioFormatRegistry::AudioFormatRegistry() : extensions_{".mp3", ".wav"} {}

bool AudioFormatRegistry::supports(const std::string& filename) const {
    const std::string extension = std::filesystem::path(filename).extension().string();
    return extensions_.contains(extension);
}