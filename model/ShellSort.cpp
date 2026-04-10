#include "ShellSort.h"

void ShellSort::arrange(std::vector<Song>& songs) {
    const int total = static_cast<int>(songs.size());
    for (int gap = total / 2; gap > 0; gap /= 2) {
        sweep(songs, gap);
    }
}

void ShellSort::sweep(std::vector<Song>& songs, const int gap) {
    const int total = static_cast<int>(songs.size());
    for (int i = gap; i < total; i++) {
        Song swapValue = songs[i];
        swapValue.accept(*this);
        const long long swapKey = key_;
        int j;
        for (j = i; j >= gap; j -= gap) {
            songs[j - gap].accept(*this);
            if (key_ <= swapKey) break;
            songs[j] = songs[j - gap];
        }
        songs[j] = swapValue;
    }
}