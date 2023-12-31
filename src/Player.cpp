#include "Player.h"
#include "Input.h"
#include "constants.h"

#include <iostream>
#include "Time.h"

Player::Player(bool isLeft)
    : m_isLeft(isLeft), Entity(new sf::RectangleShape())
{
    auto shape = dynamic_cast<sf::RectangleShape*>(m_shape);
    m_upKey = isLeft ? sf::Keyboard::W : sf::Keyboard::Up;
    m_downKey = isLeft ? sf::Keyboard::S : sf::Keyboard::Down;

    shape->setSize({10, 100});
    shape->setFillColor(sf::Color::White);

    if (m_isLeft)
    {
        m_shape->setPosition(10, 200);
    }
    else
    {
        m_shape->setPosition(WINDOW_WIDTH - 20, 200);
    }

    Size = shape->getSize();
}

void Player::Render(sf::RenderTexture& window)
{
    window.draw(*m_shape);
}

void Player::Update(sf::RenderWindow &window)
{

    if (Input::IsKeyPressed(m_upKey) && !IsCollidingUp(window))
    {
        m_shape->move(0, -PADDLE_SPEED * Time::GetDeltaTime());
    }

    if (Input::IsKeyPressed(m_downKey) && !IsCollidingDown(window))
    {
        m_shape->move(0, PADDLE_SPEED * Time::GetDeltaTime());
    }
    
    Entity::Update(window);
}

bool Player::IsCollidingUp(sf::RenderWindow &window)
{
    return m_shape->getGlobalBounds().top <= 0;
}

bool Player::IsCollidingDown(sf::RenderWindow &window)
{
    return m_shape->getGlobalBounds().top + m_shape->getGlobalBounds().height >= WINDOW_HEIGHT;
}


