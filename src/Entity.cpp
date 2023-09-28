#include "Entity.h"

#include <SFML/Graphics.hpp>

Entity::Entity(sf::Shape* shape) : m_shape(shape)
{
}

Entity::~Entity()
{
    delete m_shape;
}


void Entity::Shake()
{
    m_MissingShakeTime = SHAKE_TIME;
}

void Entity::UpdateShake(float dt)
{
    m_MissingShakeTime -= dt;
    float scale = 1.0f;

    if (m_MissingShakeTime > 0)
    {
        float t = m_MissingShakeTime / SHAKE_TIME;

        if (t > 0.5f)
        {
            scale = t;
        }
        else if (t > 0.1f)
        {
            scale = 1.1f - t;
        }
    }
    else
    {
        m_MissingShakeTime = 0;
    }

    m_shape->setScale(scale, scale);
}
