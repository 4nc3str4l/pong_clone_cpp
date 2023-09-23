#include "Ball.h"
#include "constants.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

Ball::Ball() : Entity(new sf::CircleShape())
{
    sf::CircleShape* circle = static_cast<sf::CircleShape*>(m_shape);
    circle->setRadius(10.0f);
    circle->setFillColor(sf::Color::White);
    circle->setOrigin(circle->getRadius(), circle->getRadius());
    Radius = circle->getRadius();
}

void Ball::Update(float dt, sf::RenderWindow& window)
{
    m_shape->move(m_Velocity * dt);
}

void Ball::ResetPosition()
{
    m_shape->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void Ball::ChooseInitialVelocity()
{
    float angleDeg = std::rand() % 91 - 45;
	float angleRad = angleDeg * 3.14f / 180.f;
	m_Velocity = sf::Vector2f(std::cos(angleRad), std::sin(angleRad)) * 400.f;
}

void Ball::Render(sf::RenderWindow& window)
{
    window.draw(*m_shape);
}

void Ball::CheckBoundaries()
{
	if (GetPosition().y < 0)
	{
		m_Velocity.y = -m_Velocity.y;
	}

	if (GetPosition().y + Radius * 2 > WINDOW_HEIGHT)
	{
		m_Velocity.y = -m_Velocity.y;
	}
}

void Ball::CheckCollision(const Player& player)
{
	sf::FloatRect playerBounds = player.GetBounds();
	sf::FloatRect ballBounds = GetBounds();

	if (playerBounds.intersects(ballBounds))
	{
		m_Velocity.x = -m_Velocity.x;

		float relativeY = (player.GetPosition().y + player.Size.y / 2) - (GetPosition().y + Radius);

		float maxSpeedChange = 200.f;
		m_Velocity.y += -maxSpeedChange * (relativeY / (player.Size.y / 2));
	}
}
