#include "Input.h"
#include "constants.h"

void Input::Update(sf::RenderWindow& window)
{

	for (auto event = sf::Event{}; window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			m_keysPressed[event.key.code] = true;

			if (event.key.code == sf::Keyboard::F11)
			{
				sf::VideoMode mode;
				unsigned int style;
				if (m_Fullscreen)
				{
					mode = sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
					style = sf::Style::Default;
				}
				else
				{
					mode = sf::VideoMode::getDesktopMode();
					style = sf::Style::Fullscreen;
				}

				window.create(mode, WINDOW_TITLE, style);
				m_Fullscreen = !m_Fullscreen;
			}

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
