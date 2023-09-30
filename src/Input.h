#pragma once

#include <SFML/Graphics.hpp>

class Input
{
public:
    static bool IsKeyPressed(sf::Keyboard::Key key);
    static void Update(sf::RenderWindow& window);
    inline static bool m_Fullscreen{false};
private: 
    inline static bool m_keysPressed[256];
};