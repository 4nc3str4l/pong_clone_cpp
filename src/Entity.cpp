#include "Entity.h"

#include <SFML/Graphics.hpp>

Entity::Entity(sf::Shape* shape) : m_shape(shape)
{
}

Entity::~Entity()
{
    delete m_shape;
}