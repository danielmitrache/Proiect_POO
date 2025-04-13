#ifndef PROGRESSMANAGER_H
#define PROGRESSMANAGER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
namespace ProgressManager {
    void saveChapterToFile(int chapter);
    std::vector<int> loadSavedChaptersFromFile();
}

#endif // PROGRESSMANAGER_H