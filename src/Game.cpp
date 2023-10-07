#include "Game.h"
#include "constants.h"
#include "Input.h"
#include "Utils.h"
#include "Scheduler.h"



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

    m_Ball.ResetPosition(*this);

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

    if (!m_crtShader.loadFromFile(FindInResources("./", "crt.vert"), FindInResources("./", "crt.frag")))
    {
        std::cout << "Error loading shaders" << std::endl;
        return false;
    }

    if(!m_renderTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        std::cout << "Error creating render texture" << std::endl;
        return false;
    }

    states.shader = &m_crtShader;

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
	m_crtShader.setUniform("time", m_clock.getElapsedTime().asSeconds());
	m_renderTexture.clear();

	m_ScreenRect.setFillColor({ 100, 100, 100, 10 });
	m_renderTexture.draw(m_ScreenRect);
	m_renderTexture.draw(m_MiddleLine);
	m_LeftPaddle.Render(m_renderTexture);
	m_RightPaddle.Render(m_renderTexture);
	m_Ball.Render(m_renderTexture);
	m_TopBorder.Render(m_renderTexture);
	m_BottomBorder.Render(m_renderTexture);
	m_LeftBorder.Render(m_renderTexture);
	m_RightBorder.Render(m_renderTexture);

	if (m_GameState == GameState::Starting ||
		m_GameState == GameState::Paused ||
		m_GameState == GameState::Over)
	{
		m_ScreenRect.setFillColor({ 0, 0, 0, 200 });
		m_renderTexture.draw(m_ScreenRect);
	}

	m_UI.Render(m_renderTexture);

	m_renderTexture.display();

	m_renderSprite.setTexture(m_renderTexture.getTexture());

	sf::Vector2u windowSize = Window.getSize();
	m_renderSprite.setScale(
		static_cast<float>(windowSize.x) / m_renderTexture.getSize().x,
		static_cast<float>(windowSize.y) / m_renderTexture.getSize().y
	);

	Window.draw(m_renderSprite, &m_crtShader);
}



void Game::Update(float dt)
{
    ls::Scheduler::Tick();
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
    if (m_Ball.GetPosition().x > WINDOW_WIDTH)
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
        m_Ball.ResetPosition(*this);
        m_Ball.ChooseInitialVelocity();
        SetGameState(GameState::Playing);
    }

    if (m_LeftScore != 0 || m_RightScore != 0)
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