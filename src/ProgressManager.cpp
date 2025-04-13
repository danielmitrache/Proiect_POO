#include "../include/ProgressManager.h"

namespace ProgressManager {
    void saveChapterToFile(int chapterToSave) {
        std::ifstream in("./assets/gameinfo/unlockedchapters.txt");
        if (!in.is_open()) {
            std::cerr << "Could not save progress to file" << std::endl;
            return;
        }
        std::vector<int> chapters;
        int chapter;
        while (in >> chapter) {
            chapters.push_back(chapter);
        }

        chapters.push_back(chapterToSave);
        std::sort(chapters.begin(), chapters.end());
        chapters.erase(std::unique(chapters.begin(), chapters.end()), chapters.end()); // Remove duplicates
        if (chapters[0] == 0) chapters.erase(chapters.begin()); // Remove 0 if it exists
        in.close();
        
        std::ofstream out("./assets/gameinfo/unlockedchapters.txt");
        if (!out.is_open()) {
            std::cerr << "Could not save progress to file" << std::endl;
            return;
        }
        for (const auto& ch : chapters) {
            out << ch << std::endl; // Save each chapter to the file
        }

        std::cout << "Saved chapter to file!" << std::endl;
        out.close();
    }

    std::vector<int> loadSavedChaptersFromFile(){
        std::ifstream file("./assets/gameinfo/unlockedchapters.txt");
        if (!file.is_open()) {
            std::cerr << "Could not load progress from file" << std::endl;
            return {};
        }
        std::vector<int> chapters;
        int chapter;
        while (file >> chapter) {
            chapters.push_back(chapter);
        }
        file.close();
        std::cout << "Loaded chapters from file!" << std::endl;
        return chapters;
    }
}