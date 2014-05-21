#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "../ManyMouse/manymouse.h"

#include <QtWidgets>
#include <QtGui>

#include "GameSystem.h"
#include "InputSystem.h"

using namespace Zk::Game;

GameSystem::GameSystem(int argc, char ** argv)
	: app(argc, argv)
{
	renderWindow.create(
		sf::VideoMode(800, 600),
		L"Żołdak",
		sf::Style::Titlebar | sf::Style::Close
	);
	
	renderWindow.setVerticalSyncEnabled(true);
	
	texture.loadFromFile("../data/suspended_bg.png");
	sprite.setTexture(texture, true);
}

GameSystem::~GameSystem()
{
	
}

int GameSystem::exec()
{
	sf::Vector2f position;
	sf::Clock beat;
	
	int timeForEvents;
	
	MouseDeviceHandle mdh = inputSystem.getMouseDeviceHandle(0);
	
	while (renderWindow.isOpen())
	{
		app.sendPostedEvents();
		app.processEvents(
			QEventLoop::AllEvents,
			timeForEvents
		);
		
		sf::Time frameStart = beat.getElapsedTime();
		
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
		}
		
		inputSystem.pollInput();
		
		renderWindow.clear(sf::Color::Black);
		
		sf::Vector3i mouseState = mdh.getAbsolutePosition();
		sprite.setPosition(mouseState.x, mouseState.y);
		renderWindow.draw(sprite);
		
		renderWindow.display();
		
		sf::Time frameEnd = beat.getElapsedTime();
		static const sf::Int32 millisPerFrame = 1000 / 60;
		timeForEvents = millisPerFrame - (frameEnd - frameStart).asMilliseconds();
		
		glFinish();
	}
	
	return 0;
}
