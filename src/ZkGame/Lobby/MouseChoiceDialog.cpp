#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <QDebug>

#include "../InputSystem.hpp"
#include "../GameSystem.hpp"
#include "MouseChoiceDialog.hpp"

using namespace Zk::Game;

bool MouseChoiceDialog::chooseMouse(MouseDeviceHandle & mdh)
{
	sf::Window window;
	window.create(
		sf::VideoMode(320, 240),
		"Click with the mouse you want to choose",
		sf::Style::Titlebar
	);

	InputSystem & is = GameSystem::getInstance()->getInputSystem();

	sf::Event event;
	while (true)
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::LostFocus:
				return false;

			default:
				break;
			}
		}

		is.pollInput();

		//Sprawdźmy, czy któraś myszka ma wciśnięty klawisz
		for (int i = 0; i < is.getMiceCount(); i++)
		{
			MouseDeviceHandle mdh2 = is.getMouseDeviceHandle(i);
			for (int j = 0; j < 5; j++)
			{
				if (mdh2.isButtonPressed(j))
				{
					mdh = mdh2;
					return true;
				}
			}
		}

		sf::sleep(sf::milliseconds(5));
	}

	return false;
}
