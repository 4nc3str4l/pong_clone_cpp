#pragma once

#include "Entity.h"

class Screen : public Entity
{
public:
    Screen();
    ~Screen() = default;

    void Update(float dt, sf::RenderWindow &window) override;
    void Render(sf::RenderTexture &window) override;

    void SetScreenSize(const sf::Vector2f &size);
    void SetScreenPosition(const sf::Vector2f &position);

    inline const sf::Vector2f &GetScreenSize() const { return m_ScreenSize; }
    inline const sf::Vector2f &GetScreenPosition() const { return m_ScreenPosition; }

private:
    sf::Vector2f m_ScreenSize {0.f, 0.f};
    sf::Vector2f m_ScreenPosition {0.f, 0.f};
};