#ifndef AUDIO_FORMAT_REGISTRY_H
#define AUDIO_FORMAT_REGISTRY_H

#include <set>
#include <string>

class AudioFormatRegistry final {
private:
    std::set<std::string> extensions_;

public:
    AudioFormatRegistry();
    bool supports(const std::string& filename) const;
};

#endif //AUDIO_FORMAT_REGISTRY_H