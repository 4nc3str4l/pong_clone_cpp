#pragma once

#include <SFML/Graphics.hpp>

inline const float SHAKE_TIME = 0.1f;

class Entity
{
    
public:
    Entity(sf::Shape* shape);
    virtual ~Entity();
    virtual void Render(sf::RenderTexture& window) = 0;
    virtual void Update(float dt, sf::RenderWindow& window);
    inline sf::FloatRect GetBounds() const { return m_shape->getGlobalBounds(); }
    inline sf::Vector2f GetPosition() const { return m_shape->getPosition(); }
    void Shake(float duration = SHAKE_TIME, float scale = 1.0f);
protected:
    void UpdateShake(float dt);

protected:
    sf::Shape* m_shape;

    float m_MissingShakeTime{0};
    float m_ShakeTime{SHAKE_TIME};
    float m_ShakeScale{1.0f};
};
