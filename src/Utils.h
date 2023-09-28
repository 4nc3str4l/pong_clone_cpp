#include <iostream>
#include <string>
#include <filesystem>
#include <SFML/Graphics.hpp>

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

void CenterTextX(sf::Text& text, const sf::Vector2u& windowSize) {
    // Get the bounding box of the text
    sf::FloatRect textRect = text.getLocalBounds();

    // Calculate the position to center the text in X-axis
    float xPos = (windowSize.x - textRect.width) / 2.0f;

    // Set the new position
    text.setPosition(xPos, text.getPosition().y);
}
