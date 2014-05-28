#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <Box2D/Box2D.h>
#include "../ManyMouse/manymouse.h"

#include <QtWidgets>
#include <QtGui>

#include "GameSystem.h"
#include "InputSystem.h"

using namespace Zk::Game;

GameSystem * GameSystem::instance = nullptr;

GameSystem::GameSystem(int argc, char ** argv)
	: app(argc, argv), physicsSystem()
{
	renderWindow.create(
		sf::VideoMode(800, 600),
		L"Żołdak",
		sf::Style::Titlebar | sf::Style::Close
	);
	
	renderWindow.setVerticalSyncEnabled(true);
	
	instance = this;
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
		//Wykonaj Qt-ową część programu
		app.sendPostedEvents();
		app.processEvents(
			QEventLoop::AllEvents,
			timeForEvents
		);
		
		sf::Time frameStart = beat.getElapsedTime();
		
		//Eventy SFML-a
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
		}
		
		//Eventy ManyMouse'a
		inputSystem.pollInput();
		
		//Update & render
		renderWindow.clear(sf::Color::Black);
		
		renderWindow.display();
		
		sf::Time frameEnd = beat.getElapsedTime();
		static const sf::Int32 millisPerFrame = 1000 / 60;
		timeForEvents = millisPerFrame - (frameEnd - frameStart).asMilliseconds();
		
		//Mój komputer wymaga tej funkcji, aby vsync działał poprawnie
		//Przy okazji robi kimę
		glFinish();
	}
	
	return 0;
}

InputSystem & GameSystem::getInputSystem()
{
	return inputSystem;
}
