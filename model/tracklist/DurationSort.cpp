#include "DurationSort.h"
#include "../song/FileMetadata.h"

void DurationSort::visit(const std::string&, const std::string& path) {
    key_ = FileMetadata(path).size();
}