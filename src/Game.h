#pragma once

#include <SFML/Graphics.hpp>

#include "UI.h"
#include "Player.h"
#include "Ball.h"
#include "Border.h"

enum GameState
{
    Starting,
    Playing,
    Paused,
    Over
};

enum BorderType
{
    Top,
    Bottom,
    Left,
    Right
};

class Game
{
public:
    Game();
    bool Run();

    void Render();
    void Update();

    inline GameState GetGameState() const { return m_GameState; }
    void ShakeBorder(BorderType borderType);

private:
    bool CheckIfLeftPlayerScored();
    bool CheckIfRightPlayerScored();

    void InGameUpdate(sf::RenderWindow &window);
    void StartingGame(sf::RenderWindow &window);
    void UpdatePaused(sf::RenderWindow &window);
    void UpdateGameOver(sf::RenderWindow &window);
    void SetGameState(GameState state);

    void OnPlayerScored(bool isLeftPlayer);

private:
    sf::RenderWindow Window;
    UI m_UI;

    uint8_t m_LeftScore = 0;
    uint8_t m_RightScore = 0;

    sf::VertexArray m_MiddleLine{sf::Lines, 2};

    Player m_LeftPaddle{true};
    Player m_RightPaddle{false};
    Ball m_Ball;

    Border m_TopBorder;
    Border m_BottomBorder;
    Border m_LeftBorder;
    Border m_RightBorder;

    GameState m_GameState = GameState::Starting;

    sf::RectangleShape m_ScreenRect;

    sf::Shader m_crtShader;
    sf::RenderStates states;
    sf::RenderTexture m_renderTexture;
    sf::Sprite m_renderSprite;
    sf::Clock m_clock;
};