#include <windows.h>
#include <string>
#include <iostream>
#include <format>
#include <filesystem>

std::string FindFileUpwards(const std::string& startDir, const std::string& targetFile) {
    std::filesystem::path currentDir(startDir);

    while (true) {
        std::filesystem::path absPath = std::filesystem::absolute(currentDir);
        std::string normalizedPath = absPath.string();
        if (normalizedPath.back() == '\\' || normalizedPath.back() == '/') {
            normalizedPath.pop_back();
        }

        std::string searchPattern = std::format("{}\\*", normalizedPath);

        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile(searchPattern.c_str(), &findFileData);

        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                const std::string fileName = findFileData.cFileName;
                if (fileName != "." && fileName != "..") {
                    if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && fileName == targetFile) {
                        FindClose(hFind);
                        return std::format("{}\\{}", normalizedPath, fileName);
                    }
                }
            } while (FindNextFile(hFind, &findFileData) != 0);
            FindClose(hFind);
        }

        size_t lastSeparator = normalizedPath.find_last_of("\\/");
        if (lastSeparator != std::string::npos) {
            currentDir = normalizedPath.substr(0, lastSeparator);
        } else {
            break;
        }
    }

    return "";
}