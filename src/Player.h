#pragma once

#include "Entity.h"

inline const sf::Vector2f PADDLE_SIZE{25.0f, 100.0f};
inline const float PADDLE_SPEED = 350.0f;


class Player : public Entity
{
public:
    explicit Player(bool isLeft);
    void Render(sf::RenderTexture& window) override;
    void Update(float dt, sf::RenderWindow &window) override;
private:
    bool IsCollidingUp(sf::RenderWindow &window);
    bool IsCollidingDown(sf::RenderWindow &window);

public:
    sf::Vector2f Size{0.0f, 0.0f};
private:
    sf::Keyboard::Key m_upKey;
    sf::Keyboard::Key m_downKey;

    bool m_isLeft;
};