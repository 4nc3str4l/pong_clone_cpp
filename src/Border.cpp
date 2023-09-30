#include "Border.h"

Border::Border()
    : Entity(new sf::RectangleShape())
{
}

void Border::Render(sf::RenderTexture& window)
{
    window.draw(*m_shape);
}

void Border::Update(float dt, sf::RenderWindow &window)
{
    UpdateShake(dt);
}

void Border::Set(sf::Vector2f position, sf::Vector2f size)
{
    auto rect = dynamic_cast<sf::RectangleShape *>(m_shape);
    m_shape->setPosition(position);
    rect->setSize(size);
    Size = size;
}

void Border::SetPivot(sf::Vector2f pivot)
{
    auto rect = dynamic_cast<sf::RectangleShape *>(m_shape);
    rect->setOrigin(pivot);
}
