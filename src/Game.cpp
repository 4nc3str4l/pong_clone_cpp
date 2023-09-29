#include "Game.h"
#include "constants.h"
#include "Input.h"

Game::Game() : Window{{WINDOW_WIDTH, WINDOW_HEIGHT}, WINDOW_TITLE},
 m_UI(this)
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

    m_MiddleLine[0].color = sf::Color{255, 255, 255, 100};
    m_MiddleLine[1].color = sf::Color{255, 255, 255, 100};

    // Configure the bounce.wav
    m_Ball.ResetPosition();

    m_ScreenRect.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_ScreenRect.setFillColor(sf::Color{0, 0, 0, 200});
    m_ScreenRect.setPosition(0, 0);

    // Setup borders
    int broderSize = 6;
    m_TopBorder.Set(sf::Vector2f(0, 0), sf::Vector2f(WINDOW_WIDTH, broderSize));
    m_LeftBorder.Set(sf::Vector2f(0, 0), sf::Vector2f(broderSize, WINDOW_HEIGHT));
    m_RightBorder.Set(sf::Vector2f(WINDOW_WIDTH - broderSize, 0), sf::Vector2f(broderSize, WINDOW_HEIGHT));
    
    m_BottomBorder.Set(sf::Vector2f(0, WINDOW_HEIGHT), sf::Vector2f(WINDOW_WIDTH, broderSize));
    m_BottomBorder.SetPivot(sf::Vector2f(0, broderSize));

    sf::Clock clock;
    sf::Time dt;

    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    while (Window.isOpen())
    {
        dt = clock.restart();
        timeSinceLastUpdate += dt;

        float deltaTime = timeSinceLastUpdate.asSeconds();

        Window.clear();

        Input::Update(Window);

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            Update(deltaTime);
        }

        Render();

        Window.display();
    }


    return true;
}

void Game::Render()
{


    Window.draw(m_MiddleLine);
    m_LeftPaddle.Render(Window);
    m_RightPaddle.Render(Window);
    m_Ball.Render(Window);

    m_TopBorder.Render(Window);
    m_BottomBorder.Render(Window);
    m_LeftBorder.Render(Window);
    m_RightBorder.Render(Window);

    if(m_GameState == GameState::Starting || m_GameState == GameState::Paused)
    {
        Window.draw(m_ScreenRect);
    }
    m_UI.Render(Window);

}

void Game::Update(float dt)
{

    m_UI.Update(dt, Window);

    m_LeftPaddle.Update(dt, Window);
    m_RightPaddle.Update(dt, Window);

    m_TopBorder.Update(dt, Window);
    m_BottomBorder.Update(dt, Window);
    m_LeftBorder.Update(dt, Window);
    m_RightBorder.Update(dt, Window);

    switch (m_GameState)
    {
    case GameState::Starting:
        StartingGame(dt, Window);
        break;
    case GameState::Playing:
        InGameUpdate(dt, Window);
        break;
    case GameState::Paused:
        UpdatePaused(dt, Window);
        break;
    case GameState::Over:
        UpdateGameOver(dt, Window);
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
    m_Ball.CheckBoundaries(this);


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
        ShakeBorder(BorderType::Right);
    }
    else
    {
        m_RightScore++;
        m_UI.SetRightScore(m_RightScore);
        ShakeBorder(BorderType::Left);
    }

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

#include <iostream>
void Game::ShakeBorder(BorderType borderType)
{
    switch (borderType)
    {
    case BorderType::Top:
        m_TopBorder.Shake(0.1, 2);
        break;
    case BorderType::Bottom:
        m_BottomBorder.Shake(0.1, 2);
        break;
    case BorderType::Left:
        m_LeftBorder.Shake(0.1, 2);
        break;
    case BorderType::Right:
        m_RightBorder.Shake(0.1, 2);
        break;
    }
}

void Game::StartingGame(float dt, sf::RenderWindow &window)
{
    if (Input::IsKeyPressed(sf::Keyboard::Space))
    {
        m_Ball.ResetPosition();
        m_Ball.ChooseInitialVelocity();
        SetGameState(GameState::Playing);
    }

    if(m_LeftScore != 0 || m_RightScore != 0)
    {
        m_Ball.EmitRandomParticles(10);
        m_Ball.UpdateParticles(dt);
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