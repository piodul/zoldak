#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <Box2D/Box2D.h>
#include "../ManyMouse/manymouse.h"

#include <QtWidgets>
#include <QtGui>

#include <list>
#include <memory>

#include "../ZkCommon/Constants.h"
#include "../ZkCommon/Level.h"

#include "Config/Config.h"
#include "Config/GraphicsConfig.h"
#include "Lobby/LobbyWindow.h"

#include "GameSystem.h"
#include "InputSystem.h"
#include "PlayerUI.h"
#include "Entities/Entity.h"
#include "Entities/CrateEntity.h"
#include "Entities/PlayerEntity.h"
#include "Entities/LevelMeshEntity.h"
#include "Entities/SpawnerMeshEntity.h"
#include "Entities/MouseTrackEntity.h"
#include "Renderables/Renderable.h"
#include "Camera.h"

using namespace Zk::Game;
using namespace Zk::Common;

GameSystem * GameSystem::instance = nullptr;

GameSystem::GameSystem(int argc, char ** argv)
	: physicsSystem(), playerUI(textureCache), app(argc, argv)
{
	state = State::Lobby;
	instance = this;
}

GameSystem::~GameSystem()
{
	
}

int GameSystem::exec()
{
	while (state != State::Quit)
	{
		switch (state)
		{
		case State::Lobby:
			lobbyLoop();
			break;
			
		case State::Game:
			gameLoop();
			break;
			
		default:
			//Impossibru
			break;
		}
	}
	
	return 0;
}

void GameSystem::lobbyLoop()
{
	LobbyWindow lw(config);
	lw.show();
	
	while (state == State::Lobby)
	{
		app.sendPostedEvents();
		app.processEvents(
			QEventLoop::WaitForMoreEvents,
			250
		);
	}
}

void GameSystem::initializeGameLoop()
{
	renderWindow.create(
		//sf::VideoMode(800, 600),
		config.graphicsConfig.videoMode,
		L"Żołdak",
		sf::Style::Titlebar | sf::Style::Close
	);
	
	//Ustaw ikonę okna
	{
		sf::Image wndIcon;
		if (wndIcon.loadFromFile("../data/grenade.png"))
		{	
			sf::Vector2u iconSize = wndIcon.getSize();
			
			renderWindow.setIcon(
				iconSize.x,
				iconSize.y,
				wndIcon.getPixelsPtr()
			);
		}
	}
	
	renderWindow.setVerticalSyncEnabled(true);
	
	Level l;
	QFile f("../bin/multilayer.zvl");
	if (!f.open(QIODevice::ReadOnly))
		qDebug() << "Failed to open level";
	else
	{
		QDataStream ds(&f);
		ds >> l;
	}
	
	entities.push_back(
		std::make_shared<LevelMeshEntity>(
			l.getLayers()[(int)LayerType::MIDGROUND]
		)
	);
	
	entities.push_back(
		std::make_shared<SpawnerMeshEntity>(
			l.getLayers()[(int)LayerType::MEDKIT_SPAWN],
			LayerType::MEDKIT_SPAWN
		)
	);
	
	entities.push_back(
		std::make_shared<SpawnerMeshEntity>(
			l.getLayers()[(int)LayerType::GRENADES_SPAWN],
			LayerType::GRENADES_SPAWN
		)
	);
	
	{
		std::shared_ptr<Entity> ent = std::make_shared<MouseTrackEntity>(
			inputSystem.getMouseDeviceHandle(0)
		);
		entities.push_back(ent);
		
		auto player = std::make_shared<PlayerEntity>(sf::Vector2f(-1.5f, -1.f));
		player->registerMe();
		entities.push_back(player);
		
		this->player = player;
	}
	
	camera = new SplitScreenCamera({ player });
}

void GameSystem::gameLoop()
{
	initializeGameLoop();
	
	sf::Vector2f position;
	sf::Clock beat;
	
	int timeForEvents;
	
	//renderWindow.setFramerateLimit(60);
	
	while (state == State::Game)
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
			{
				renderWindow.close();
				state = State::Lobby;
			}
		}
		
		//Eventy ManyMouse'a
		inputSystem.pollInput();
		
		//Fizyka
		physicsSystem.simulate(1.0 / 60.0);
		
		//Update
		for (std::shared_ptr<Entity> ent : entities)
			ent->update(1.0 / 60.0);
		
		//Render
		renderWindow.clear(sf::Color::White);
		
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
		
		//Teraz rysujemy UI w specjalnym viewporcie
		//for (sf::View view : views)
		{
			sf::View view = views[0];
			sf::VideoMode confVideoMode = config.graphicsConfig.videoMode;
			sf::Vector2u viewSize(confVideoMode.width, confVideoMode.height);
			view.reset(sf::FloatRect(0.f, 0.f, viewSize.x, viewSize.y));
			renderWindow.setView(view);
			
			sf::FloatRect fr = view.getViewport();
			fr.left *= (float)viewSize.x;
			fr.top *= (float)viewSize.y;
			fr.width *= (float)viewSize.x;
			fr.height *= (float)viewSize.y;
			
			playerUI.paint(&renderWindow, player, fr);
		}
		
		renderWindow.display();
		glFlush();
		
		//Wszystko się narysowało, więc możemy teraz pousuwać
		//nieaktywne obiekty
		entities.remove_if(
			[](const std::shared_ptr<Entity> & ent) -> bool
			{
				if (ent->wantsToBeDeleted())
					qDebug() << "Removing entity!";
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
	
	cleanupGameLoop();
}

void GameSystem::cleanupGameLoop()
{
	entities.clear();
	delete camera;
}

void GameSystem::changeState(State s)
{
	state = s;
}

void GameSystem::addEntity(std::shared_ptr<Entity> ent)
{
	entities.push_back(ent);
}
