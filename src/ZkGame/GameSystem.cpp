#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "../ManyMouse/manymouse.h"

#include "GameSystem.h"

using namespace Zk::Game;

GameSystem::GameSystem()
{
	ManyMouse_Init();
	
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
	ManyMouse_Quit();
}

int GameSystem::run()
{
	sf::Vector2f position;
	
	while (renderWindow.isOpen())
	{
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
		}
		
		ManyMouseEvent mme;
		while (ManyMouse_PollEvent(&mme))
		{
			switch (mme.type)
			{
			case MANYMOUSE_EVENT_ABSMOTION:
				if (mme.item == 0)
					position.x = mme.value;
				else if (mme.item == 1)
					position.y = mme.value;
				break;
				
			case MANYMOUSE_EVENT_RELMOTION:
				if (mme.item == 0)
					position += sf::Vector2f(mme.value, 0);
				else if (mme.item == 1)
					position += sf::Vector2f(0, mme.value);
				break;
				
			case MANYMOUSE_EVENT_BUTTON:
				
				break;
				
			case MANYMOUSE_EVENT_SCROLL:
				
				break;
				
			case MANYMOUSE_EVENT_DISCONNECT:
				
				break;
				
			case MANYMOUSE_EVENT_MAX:
				
				break;
				
			}
		}
		
		renderWindow.clear(sf::Color::Black);
		
		sprite.setPosition(position);
		renderWindow.draw(sprite);
		
		renderWindow.display();
		glFinish();
	}
	
	return 0;
}
