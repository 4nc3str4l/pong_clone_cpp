#pragma once

#include "Entity.h"
#include "ParticleEmitter.h"

class Player;

inline const float EMISSION_RATE = 0.01f;

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
    void EmitRandomParticles(int num);

public:
    float Radius{0.0f};

private:
    sf::Vector2f m_Velocity{0.0f, 0.0f};
    float m_NextParticleEmit {0.0f};
    ParticleEmitter m_ParticleEmitter;
};