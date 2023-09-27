#include "Game.h"
#include "constants.h"
#include "Input.h"

Game::Game() : m_Window{{WINDOW_WIDTH, WINDOW_HEIGHT}, WINDOW_TITLE}, m_UI(this)
{
}

bool Game::Run()
{

    if (!m_UI.Init())
    {
        return false;
    }

    m_MiddleLine[0].position = sf::Vector2f(370, 0);
    m_MiddleLine[1].position = sf::Vector2f(370, 500);

    m_MiddleLine[0].color = sf::Color::White;
    m_MiddleLine[1].color = sf::Color::White;

    // Configure the ball
    m_Ball.ResetPosition();

    sf::Clock clock;
    sf::Time dt;

    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    while (m_Window.isOpen())
    {
        dt = clock.restart();
        timeSinceLastUpdate += dt;

        float deltaTime = timeSinceLastUpdate.asSeconds();

        m_Window.clear();

        Input::Update(m_Window);

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            Update(deltaTime);
        }

        Render();

        m_Window.display();
    }


    return true;
}

void Game::Render()
{
    m_Window.draw(m_MiddleLine);
    m_LeftPaddle.Render(m_Window);
    m_RightPaddle.Render(m_Window);
    m_Ball.Render(m_Window);
    m_UI.Render(m_Window);
}

void Game::Update(float dt)
{

    m_UI.Update(dt, m_Window);

    m_LeftPaddle.Update(dt, m_Window);
    m_RightPaddle.Update(dt, m_Window);

    switch (m_GameState)
    {
    case GameState::Starting:
        StartingGame(dt, m_Window);
        break;
    case GameState::Playing:
        InGameUpdate(dt, m_Window);
        break;
    case GameState::Paused:
        UpdatePaused(dt, m_Window);
        break;
    case GameState::Over:
        UpdateGameOver(dt, m_Window);
        break;
    default:
        break;
    }
}

bool Game::CheckIfLeftPlayerScored()
{
    if (m_Ball.GetPosition().x > 740)
    {
        return true;
    }
    return false;
}

bool Game::CheckIfRightPlayerScored()
{
    if (m_Ball.GetPosition().x < 0)
    {
        return true;
    }
    return false;
}

void Game::InGameUpdate(float dt, sf::RenderWindow &window)
{
    m_Ball.Update(dt, window);
    m_Ball.CheckCollision(m_LeftPaddle);
    m_Ball.CheckCollision(m_RightPaddle);
    m_Ball.CheckBoundaries();

    if (CheckIfLeftPlayerScored())
    {
        OnPlayerScored(true);
    }
    else if (CheckIfRightPlayerScored())
    {
        OnPlayerScored(false);
    }

    if (Input::IsKeyPressed(sf::Keyboard::P))
    {
		SetGameState(GameState::Paused);
	}
}

void Game::OnPlayerScored(bool isLeftPlayer)
{
    if (isLeftPlayer)
    {
        m_LeftScore++;
        m_UI.SetLeftScore(m_LeftScore);
    }
    else
    {
        m_RightScore++;
        m_UI.SetRightScore(m_RightScore);
    }

    m_Ball.ResetPosition();
    if (m_LeftScore == 5 || m_RightScore == 5)
    {
        m_GameState = GameState::Over;
        m_UI.SetWinner(m_LeftScore == 5);
    }
    else
    {
        SetGameState(GameState::Starting);
    }
}

void Game::StartingGame(float dt, sf::RenderWindow &window)
{
    if (Input::IsKeyPressed(sf::Keyboard::Space))
    {
        m_Ball.ChooseInitialVelocity();
        SetGameState(GameState::Playing);
    }
}

void Game::UpdatePaused(float dt, sf::RenderWindow &window)
{
    if (Input::IsKeyPressed(sf::Keyboard::Space))
    {
        SetGameState(GameState::Playing);
    }
}

void Game::UpdateGameOver(float dt, sf::RenderWindow &window)
{
    if (Input::IsKeyPressed(sf::Keyboard::R))
    {
        m_LeftScore = 0;
        m_RightScore = 0;
        m_UI.SetLeftScore(m_LeftScore);
        m_UI.SetRightScore(m_RightScore);
        SetGameState(GameState::Starting);
    }
}

void Game::SetGameState(GameState state)
{
    m_GameState = state;
    switch (m_GameState)
    {
    case GameState::Starting:
        m_UI.SetInstruction("Press Space to start");
        break;
    case GameState::Playing:
        m_UI.SetInstruction("");
        break;
    case GameState::Paused:
        m_UI.SetInstruction("Press P to resume");
        break;
    case GameState::Over:
        m_UI.SetInstruction("Press R to restart");
        break;
    default:
        break;
    }
}