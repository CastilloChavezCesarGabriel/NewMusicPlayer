#include "FormatRegistry.h"
#include <filesystem>

FormatRegistry::FormatRegistry() : extensions_{".mp3", ".wav"} {}

bool FormatRegistry::supports(const std::string& filename) const {
    const std::string extension = std::filesystem::path(filename).extension().string();
    return extensions_.contains(extension);
}