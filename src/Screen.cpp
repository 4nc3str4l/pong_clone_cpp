#include "Screen.h"


Screen::Screen() : Entity(nullptr)
{
}

void Screen::Update(sf::RenderWindow& window)
{
	Entity::Update(window);
}

void Screen::Render(sf::RenderTexture &window)
{
}

void Screen::SetScreenSize(const sf::Vector2f &size)
{
}

void Screen::SetScreenPosition(const sf::Vector2f &position)
{
}
