#ifndef SHELL_SORT_H
#define SHELL_SORT_H

#include "IArrangementStrategy.h"
#include "ISongVisitor.h"

class ShellSort : public IArrangementStrategy, public ISongVisitor {
protected:
    long long key_ = 0;

private:
    void sweep(std::vector<Song>& songs, int gap);

public:
    void arrange(std::vector<Song>& songs) override;
};

#endif //SHELL_SORT_H
