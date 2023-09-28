#include <iostream>
#include <string>
#include <filesystem>

std::string FindFileUpwards(const std::filesystem::path& startDir, const std::string& targetFile) {
    std::filesystem::path currentDir = std::filesystem::absolute(startDir);

    while (!currentDir.empty()) {
        std::filesystem::directory_iterator dirIt(currentDir), end;

        for (; dirIt != end; ++dirIt) {
            if (dirIt->is_regular_file() && dirIt->path().filename() == targetFile) {
                return dirIt->path().string();
            }
        }

        if (currentDir.has_parent_path()) {
            std::filesystem::path parentDir = currentDir.parent_path();
            if (parentDir != currentDir) {
                currentDir = parentDir;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    return "";
}