#pragma once

#include <SFML/Graphics.hpp>

inline const float SHAKE_TIME = 0.1f;

class Entity
{
    
public:
    Entity(sf::Shape* shape);
    virtual ~Entity();
    virtual void Render(sf::RenderWindow& window) = 0 ;
    virtual void Update(float dt, sf::RenderWindow& window) = 0;
    inline sf::FloatRect GetBounds() const { return m_shape->getGlobalBounds(); }
    inline sf::Vector2f GetPosition() const { return m_shape->getPosition(); }
    void Shake();
protected:
    void UpdateShake(float dt);

protected:
    sf::Shape* m_shape;

    float m_MissingShakeTime{0};
};
