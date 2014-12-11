#include <SFML/Window.hpp>

#include "../Config/InputAction.hpp"
#include "InputChoiceDialog.hpp"

using namespace Zk::Game;

bool InputChoiceDialog::chooseInputAction(InputAction & ia)
{
	sf::Window window;
	window.create(
		sf::VideoMode(320, 240),
		"Choose key",
		sf::Style::Titlebar
	);

	sf::Event event;
	while (window.waitEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::LostFocus:
			return false;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Unknown)
				break;

			ia = InputAction(event.key.code);
			return true;

		case sf::Event::MouseButtonPressed:
			ia = InputAction(event.mouseButton.button);
			return true;

		default:
			break;
		}
	}

	return false;
}
