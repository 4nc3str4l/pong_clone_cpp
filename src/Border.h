#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>

class Border : public Entity
{
public:
    Border();
    void Render(sf::RenderTexture& window) override;
    void Update(sf::RenderWindow &window) override;
    void Set(sf::Vector2f position, sf::Vector2f size);
    void SetPivot(sf::Vector2f pivot);
private:
    sf::Vector2f Size{0.0f, 0.0f};
};
