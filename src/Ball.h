#pragma once

#include "Entity.h"

class Player;

class Ball : public Entity
{
public:
    Ball();
    void Update(float dt, sf::RenderWindow &window) override;
    void Render(sf::RenderWindow &window) override;
    void ChooseInitialVelocity();
    void ResetPosition();
    void CheckBoundaries();
    void CheckCollision(const Player& player);

public:
    float Radius{0.0f};

private:
    sf::Vector2f m_Velocity{0.0f, 0.0f};
};