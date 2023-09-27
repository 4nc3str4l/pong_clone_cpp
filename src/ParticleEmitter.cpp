#include "ParticleEmitter.h"
#include <algorithm>

void ParticleEmitter::Update(float dt)
{
    for(auto &p : m_Particles)
    {
        if(p.Lifetime > 0.f)
        {
            p.Position += p.Velocity * dt;
            p.Lifetime -= dt;
        }
    }
}

void ParticleEmitter::Render(sf::RenderWindow &window)
{
    m_Shape.setOrigin(m_Shape.getRadius(), m_Shape.getRadius());
    for(auto &p : m_Particles)
    {
        if(p.Lifetime > 0.f)
        {
            m_Shape.setPosition(p.Position);
            window.draw(m_Shape);

            // Change alpha value of the particle
            p.Color.a = static_cast<sf::Uint8>(p.Lifetime/0.5f * 255.f);
            m_Shape.setFillColor(p.Color);

        }
    }
}

void ParticleEmitter::Emit(const sf::Vector2f &position,
                            const sf::Vector2f &velocity,
                            float lifetime, sf::Color color)
{
    auto it = std::find_if(m_Particles.begin(), m_Particles.end(),
                           [](const Particle &p) { return p.Lifetime <= 0.f; });

    if(it != m_Particles.end())
    {
        it->Position = position;
        it->Velocity = velocity;
        it->Lifetime = lifetime;
        it->Color = color;
    }
    else
    {
        m_Particles.emplace_back(Particle{position, velocity, color, lifetime});
    }
}