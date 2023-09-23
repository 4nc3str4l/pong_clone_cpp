#pragma once

#include <SFML/Graphics.hpp>

#include "UI.h"
#include "Player.h"
#include "Ball.h"

enum class GameState
{
    Starting,
    Playing,
    Paused,
    Over
};

class Game
{
public:
    Game();
    bool Run();

    void Render();
    void Update(float dt);

    inline GameState GetGameState() const { return m_GameState; }

private:
    bool CheckIfLeftPlayerScored();
    bool CheckIfRightPlayerScored();

    void InGameUpdate(float dt, sf::RenderWindow &window);
    void StartingGame(float dt, sf::RenderWindow &window);
    void UpdatePaused(float dt, sf::RenderWindow &window);
    void UpdateGameOver(float dt, sf::RenderWindow &window);
    void SetGameState(GameState state);

    void OnPlayerScored(bool isLeftPlayer);

private:
    UI m_UI;

    uint8_t m_LeftScore = 0;
    uint8_t m_RightScore = 0;

    sf::VertexArray m_MiddleLine{sf::Lines, 2};

    Player m_LeftPaddle{true};
    Player m_RightPaddle{false};
    Ball m_Ball;

    GameState m_GameState = GameState::Starting;

    sf::RenderWindow m_Window;
};