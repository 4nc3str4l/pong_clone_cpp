#pragma once

#include <SFML/Graphics.hpp>

class Game;

class UI
{
public:
    UI(Game* game);
    bool Init();

    void Render(sf::RenderTexture& window);
    void Update(float dt, sf::RenderWindow& window);

    void SetLeftScore(uint8_t score);
    void SetRightScore(uint8_t score);

    void SetWinner(bool isLeftPlayer);

    void SetInstruction(const std::string& instruction);

private: 
    sf::Text leftScore;
    sf::Text rightScore;
    sf::Text instructions;
    sf::Text winner;
    sf::Font font;


    Game* m_Game;
};