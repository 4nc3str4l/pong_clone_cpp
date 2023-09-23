#include "Player.h"
#include "Input.h"

Player::Player(bool isLeft)
    : m_isLeft(isLeft), Entity(new sf::RectangleShape())
{
    sf::RectangleShape* shape = static_cast<sf::RectangleShape*>(m_shape);
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
        m_shape->setPosition(720, 200);
    }

    Size = shape->getSize();
}

void Player::Render(sf::RenderWindow &window)
{
    window.draw(*m_shape);
}

void Player::Update(float dt, sf::RenderWindow &window)
{

    if (Input::IsKeyPressed(m_upKey) && !IsCollidingUp(window))
    {
        m_shape->move(0, -PADDLE_SPEED * dt);
    }

    if (Input::IsKeyPressed(m_downKey) && !IsCollidingDown(window))
    {
        m_shape->move(0, PADDLE_SPEED * dt);
    }
}

bool Player::IsCollidingUp(sf::RenderWindow &window)
{
    return m_shape->getGlobalBounds().top <= 0;
}

bool Player::IsCollidingDown(sf::RenderWindow &window)
{
    return m_shape->getGlobalBounds().top + m_shape->getGlobalBounds().height >= window.getSize().y;
}
