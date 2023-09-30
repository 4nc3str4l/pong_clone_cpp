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

void ParticleEmitter::Render(sf::RenderTexture& window)
{

    for(auto &p : m_Particles)
    {
        if(p.Lifetime > 0.f)
        {
            m_Shape.setPosition(p.Position);

            // Change alpha value of the particle
            p.Color.a = static_cast<sf::Uint8>(p.Lifetime / p.InitialLifetime * 255.f);
            m_Shape.setFillColor(p.Color);

            // Change size of the particle based on its lifetime
            m_Shape.setRadius(p.Lifetime / p.InitialLifetime * p.InitialRadius);
            m_Shape.setOrigin(m_Shape.getRadius(), m_Shape.getRadius());

            window.draw(m_Shape);
        }
    }
}

void ParticleEmitter::Emit(const sf::Vector2f &position,
                            const sf::Vector2f &velocity,
                            float lifetime,
                            sf::Color color,
                            float radius)
{
    auto it = std::find_if(m_Particles.begin(), m_Particles.end(),
                           [](const Particle &p) { return p.Lifetime <= 0.f; });

    if(it != m_Particles.end())
    {
        it->Position = position;
        it->Velocity = velocity;
        it->Lifetime = lifetime;
        it->InitialLifetime = lifetime;
        it->Color = color;
        it->InitialRadius = radius;
    }
    else
    {
        m_Particles.emplace_back(Particle{position, velocity,
                                          color, lifetime,
                                          lifetime,
                                          radius});
    }
}