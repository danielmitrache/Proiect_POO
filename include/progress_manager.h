#ifndef PROGRESSMANAGER_H
#define PROGRESSMANAGER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
namespace Progress_Manager {
    void saveChapterToFile(int chapter);
    std::vector<int> loadSavedChaptersFromFile();
}

#endif // PROGRESSMANAGER_H