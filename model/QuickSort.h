#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "IArrangementStrategy.h"
#include "ISongVisitor.h"
#include <utility>

class QuickSort final : public IArrangementStrategy, public ISongVisitor {
private:
    std::string title_;

    void visit(const std::string& name, const std::string& path) override;
    int divide(std::vector<Song>& songs, const std::pair<int, int>& bounds);

public:
    void arrange(std::vector<Song>& songs) override;
};

#endif //QUICK_SORT_H
