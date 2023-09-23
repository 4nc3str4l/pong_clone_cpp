#include "Input.h"

void Input::Update(sf::RenderWindow& window)
{
    for (auto event = sf::Event{}; window.pollEvent(event);)
	{
        switch(event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                m_keysPressed[event.key.code] = true;
                break;
            case sf::Event::KeyReleased:
                m_keysPressed[event.key.code] = false;
                break;
            default:
                break;
        }
	}
}

bool Input::IsKeyPressed(sf::Keyboard::Key key)
{
    return m_keysPressed[key];
}