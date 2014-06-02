#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <Box2D/Box2D.h>
#include "../ManyMouse/manymouse.h"

#include <QtWidgets>
#include <QtGui>

#include <list>
#include <memory>

#include "../ZkCommon/Level.h"

#include "GameSystem.h"
#include "InputSystem.h"
#include "Entities/Entity.h"
#include "Entities/CrateEntity.h"
#include "Entities/PlayerEntity.h"
#include "Entities/LevelMeshEntity.h"
#include "Entities/MouseTrackEntity.h"
#include "Renderables/Renderable.h"
#include "Camera.h"

using namespace Zk::Game;
using namespace Zk::Common;

GameSystem * GameSystem::instance = nullptr;

GameSystem::GameSystem(int argc, char ** argv)
	: physicsSystem(), app(argc, argv)
{
	renderWindow.create(
		sf::VideoMode(800, 600),
		L"Żołdak",
		sf::Style::Titlebar | sf::Style::Close
	);
	
	renderWindow.setVerticalSyncEnabled(true);
	
	instance = this;
	
	Level l;
	QFile f("../bin/box2.zvl");
	if (!f.open(QIODevice::ReadOnly))
		qDebug() << "Failed to open level";
	else
	{
		QDataStream ds(&f);
		ds >> l;
	}
	
	entities.push_back(
		std::make_shared<LevelMeshEntity>(
			l.getLayers()[0]
		)
	);
	
	std::shared_ptr<Entity> ent = std::make_shared<MouseTrackEntity>(
		inputSystem.getMouseDeviceHandle(0)
	);
	entities.push_back(ent);
	
	auto crate = std::make_shared<CrateEntity>(sf::Vector2f(0.f, -2.f));
	entities.push_back(crate);
	
	auto crate2 = std::make_shared<CrateEntity>(sf::Vector2f(0.5f, -1.f));
	entities.push_back(crate2);
	auto crate3 = std::make_shared<CrateEntity>(sf::Vector2f(1.5f, -1.f));
	entities.push_back(crate3);
	auto player = std::make_shared<PlayerEntity>(sf::Vector2f(-1.5f, -1.f));
	player->registerMe();
	entities.push_back(player);
	
	camera = new SplitScreenCamera({ player });
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
	
	//renderWindow.setFramerateLimit(60);
	
	while (renderWindow.isOpen())
	{
		//Wykonaj Qt-ową część programu
		sf::Time frameStart = beat.getElapsedTime();
		
		app.sendPostedEvents();
		app.processEvents(
			QEventLoop::AllEvents,
			timeForEvents
		);
		
		sf::Time qtLoopFinished = beat.getElapsedTime();
		
		//qDebug() << (qtLoopFinished - frameStart).asMilliseconds();
		
		//Eventy SFML-a
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
		}
		
		//Eventy ManyMouse'a
		inputSystem.pollInput();
		
		//Fizyka
		physicsSystem.simulate(1.0 / 60.0);
		
		//Update
		for (std::shared_ptr<Entity> ent : entities)
			ent->update(1.0 / 60.0);
		
		//Render
		renderWindow.clear(sf::Color::Black);
		
		camera->setupViews();
		std::vector<sf::View> views = camera->getViews();
		
		for (sf::View view : views)
		{
			renderWindow.setView(view);
			for (std::shared_ptr<Entity> ent : entities)
			{
				Renderable * r = ent->getRenderable();
				if (r)
					r->paint(&renderWindow);
			}
		}
		
		renderWindow.display();
		glFlush();
		
		//Wszystko się narysowało, więc możemy teraz pousuwać
		//nieaktywne obiekty
		entities.remove_if(
			[](const std::shared_ptr<Entity> & ent) -> bool
			{
				return ent->wantsToBeDeleted();
			}
		);
		
		//Wprawdzie SFML posiada mechanizmy pozwalające na ograniczenie
		//framerate, lecz robi to trochę nieudolnie i pojawiają się lagi.
		//Nie wynikają one prawdopodobnie z niekompetencji programisty,
		//lecz z dużej ziarnistości sleep-a.
		//Użycie glFinish z drugiej strony daje perfekcyjną synchronizację,
		//lecz powoduje loop-spinning i zżera u mnie 20% CPU.
		//Moje rozwiązanie łączy obydwa podejścia: po zakończeniu pętli
		//wątek zasypia i budzi się 1-2ms przed odpaleniem glFinish,
		//które czeka na odświeżenie ekranu.
		//Nie rozwiązuje to jednak fundamentalnego problemu - wszystko
		//się popsuje gdy monitor będzie miał inną częstotliwość odświeżania
		//niż 60Hz. To jest do poprawienia.
		
		sf::Time frameEnd = beat.getElapsedTime();
		static const sf::Int32 millisPerFrame = 1000 / 60;
		timeForEvents =
			millisPerFrame - (qtLoopFinished - frameStart).asMilliseconds();
		
		//Śpimy, bo glFinish() robi aktywne czekanie
		int timeToSleep = millisPerFrame - (frameEnd - frameStart).asMilliseconds();
		timeToSleep = std::max(timeToSleep - 3, 0);
		QThread::currentThread()->msleep(timeToSleep);
		
		//Mój komputer wymaga tej funkcji, aby vsync działał poprawnie
		//Zasraniec robi aktywne czekanie, though
		glFinish();
	}
	
	return 0;
}
