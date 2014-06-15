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
#include "Player.h"
#include "PlayerUI.h"
#include "SpawnerMesh.h"
#include "Entities/Entity.h"
#include "Entities/CrateEntity.h"
#include "Entities/PlayerEntity.h"
#include "Entities/LevelMeshEntity.h"
#include "Entities/SpawnerMeshEntity.h"
#include "Entities/MouseTrackEntity.h"
#include "Entities/PlayerTrackEntity.h"
#include "Renderables/Renderable.h"
#include "Weapons/WeaponDef.h"
#include "Weapons/Weapon.h"
#include "Camera.h"

using namespace Zk::Game;
using namespace Zk::Common;

GameSystem * GameSystem::instance = nullptr;

GameSystem::GameSystem(int argc, char ** argv)
	: app(argc, argv), physicsSystem(), playerUI(textureCache)
{
	state = State::Lobby;
	instance = this;
	hasFocus = true;
}

GameSystem::~GameSystem()
{
	
}

int GameSystem::exec()
{
	loadConfig();
	
	while (state != State::Quit)
	{
		switch (state)
		{
		case State::Lobby:
			lobbyLoop();
			saveConfig();
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
		
		QThread::currentThread()->msleep(10);
	}
}

void GameSystem::initializeGameLoop()
{
	{
		sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;
		if (config.graphicsConfig.fullscreen)
			style |= sf::Style::Fullscreen;
		
		renderWindow.create(
			//sf::VideoMode(800, 600),
			config.graphicsConfig.videoMode,
			L"Żołdak",
			style
		);
		
		renderWindow.setMouseCursorVisible(false);
	}
	
	//Ustaw ikonę okna
	{
		sf::Image wndIcon;
		if (wndIcon.loadFromFile(
			resourcePath("grenade.png"))
		)
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
	QFile f(resourcePath("../bin/multilayer.zvl").c_str());
	if (!f.open(QIODevice::ReadOnly))
		qDebug() << "Failed to open level";
	else
	{
		QDataStream ds(&f);
		ds >> l;
	}
	
	addEntity(
		std::make_shared<LevelMeshEntity>(
			l.getLayers()[(int)LayerType::FOREGROUND],
			LayerType::FOREGROUND
		)
	);
	
	addEntity(
		std::make_shared<LevelMeshEntity>(
			l.getLayers()[(int)LayerType::MIDGROUND],
			LayerType::MIDGROUND
		)
	);
	
	addEntity(
		std::make_shared<LevelMeshEntity>(
			l.getLayers()[(int)LayerType::BACKGROUND],
			LayerType::BACKGROUND
		)
	);
	
	addEntity(
		std::make_shared<SpawnerMeshEntity>(
			l.getLayers()[(int)LayerType::MEDKIT_SPAWN],
			LayerType::MEDKIT_SPAWN
		)
	);
	
	addEntity(
		std::make_shared<SpawnerMeshEntity>(
			l.getLayers()[(int)LayerType::GRENADES_SPAWN],
			LayerType::GRENADES_SPAWN
		)
	);
	
	{
		WeaponDef wd;
		wd.damagePerShot = 15.0;
		wd.muzzleVelocity = 100.0;
		wd.refireTime = 0.05;
		wd.reloadTime = 3.0;
		wd.clipSize = 30;
		
		players[0].setMouseDevice(inputSystem.getMouseDeviceHandle(0));
		players[0].setSpawnerMesh(SpawnerMesh(
			l.getLayers()[(int)LayerType::PLAYER_A_SPAWN]
		));
		players[0].setInputConfig(config.playerInputConfig[0]);
		players[0].setWeaponDef(wd);
		
		players[1].setMouseDevice(inputSystem.getMouseDeviceHandle(1));
		players[1].setSpawnerMesh(SpawnerMesh(
			l.getLayers()[(int)LayerType::PLAYER_B_SPAWN]
		));
		players[1].setInputConfig(config.playerInputConfig[1]);
		players[1].setWeaponDef(wd);
	}
	
	auto track = std::make_shared<PlayerTrackEntity>(0);
	auto track2 = std::make_shared<PlayerTrackEntity>(1);
	entities.push_back(track);
	entities.push_back(track2);
	
	camera = new SplitScreenCamera({ track, track2 });
	
	{
		// std::shared_ptr<Entity> ent = std::make_shared<MouseTrackEntity>(
		// 	inputSystem.getMouseDeviceHandle(0)
		// );
		// entities.push_back(ent);
		
		// auto player = std::make_shared<PlayerEntity>(
		// 	sf::Vector2f(-1.5f, -1.f),
		// 	config.playerInputConfig[0],
		// 	inputSystem.getMouseDeviceHandle(0),
		// 	wd
		// );
		// player->registerMe();
		
		// auto player2 = std::make_shared<PlayerEntity>(
		// 	sf::Vector2f(1.5f, -1.f),
		// 	config.playerInputConfig[1],
		// 	inputSystem.getMouseDeviceHandle(1),
		// 	wd
		// );
		// player2->registerMe();
		
		// addEntity(player);
		// addEntity(player2);
		
		// this->players = { player, player2 };
		// camera = new SplitScreenCamera({ player, player2 });
	}
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
			else if (event.type == sf::Event::GainedFocus)
				hasFocus = true;
			else if (event.type == sf::Event::MouseButtonPressed)
				hasFocus = true;
			else if (event.type == sf::Event::LostFocus)
				hasFocus = false;
		}
		
		//Eventy ManyMouse'a
		inputSystem.pollInput();
		
		//Fizyka
		physicsSystem.simulate(1.0 / 60.0);
		
		//Niektóre jednostki mogą chcieć skorzystać z widoków kamery
		camera->setupViews();
		
		players[0].update(1.0 / 60.0);
		players[1].update(1.0 / 60.0);
		
		//Update
		for (std::shared_ptr<Entity> ent : entities)
			ent->update(1.0 / 60.0);
		
		//Render
		removeInactiveRenderables();
		refreshZOrder();
		
		renderWindow.clear(sf::Color::White);
		
		std::vector<sf::View> views = camera->getViews();
		
		for (sf::View view : views)
		{
			renderWindow.setView(view);
			for (auto p : renderables)
			{
				auto ptr = p.second.lock();
				ptr->paint(&renderWindow);
			}
		}
		
		//Teraz rysujemy UI w specjalnym viewporcie
		int viewid = 0;
		for (sf::View view : views)
		{
			sf::Vector2f viewSize =
				view.getSize() * (float)Constants::PIXELS_PER_METER;
			view.reset(sf::FloatRect(0.f, 0.f, viewSize.x, viewSize.y));
			renderWindow.setView(view);
			
			sf::FloatRect fr = view.getViewport();
			fr.left *= 0.f;
			fr.top *= 0.f;
			fr.width *= (float)viewSize.x;
			fr.height *= (float)viewSize.y;
			
			playerUI.paint(
				&renderWindow,
				players[viewid].getPlayerEntity(),
				fr
			);
			viewid++;
		}
		
		renderWindow.display();
		glFlush();
		
		//Wszystko się narysowało, więc możemy teraz pousuwać
		//nieaktywne obiekty
		removeInactiveEntities();
		
		//Przesuwamy kursor myszy z powrotem na środek okienka, aby
		//nie "wylazł" poza jego obszar.
		//Jest to nie do końca ładny trik, gdyż okazjonalnie, przy
		//szybkich ruchach myszki, kursor może wylecieć za okno.
		//Nie ma to znaczenia, na szczęście, w trybie fullscreen.
		//Różne systemy operacyjne udostępniają opcję ograniczenia
		//ruchów kursora do obszaru okna, lecz w SFML-u ficzer ten
		//jest dopiero w przygotowaniu:
		//	https://github.com/LaurentGomila/SFML/issues/394
		//	https://github.com/LaurentGomila/SFML/issues/394
		if (hasFocus)
			sf::Mouse::setPosition(
				(sf::Vector2i)renderWindow.getSize() / 2,
				renderWindow
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

void GameSystem::removeInactiveEntities()
{
	entities.remove_if(
		[](const std::shared_ptr<Entity> & ent) -> bool
		{
			if (ent->wantsToBeDeleted())
				qDebug() << "Removing entity!";
			return ent->wantsToBeDeleted();
		}
	);
}

void GameSystem::removeInactiveRenderables()
{
	for (auto it = renderables.begin(); it != renderables.end();)
	{
		if (it->second.expired())
			renderables.erase(it++);
		else
			it++;
	}
}

void GameSystem::refreshZOrder()
{
	std::vector<std::weak_ptr<Renderable>> renderablesToChange;
	for (auto it = renderables.begin(); it != renderables.end();)
	{
		auto ptr = it->second.lock();
		if (it->first != ptr->getZValue())
		{
			renderablesToChange.push_back(it->second);
			renderables.erase(it++);
		}
		else
			it++;
	}
	
	for (std::weak_ptr<Renderable> r : renderablesToChange)
		renderables.insert(
			std::make_pair(r.lock()->getZValue(), r)
		);
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
	
	std::weak_ptr<Renderable> r = ent->getRenderable();
	auto ptr = r.lock();
	
	if (ptr != nullptr)
		renderables.insert(
			std::make_pair(r.lock()->getZValue(), r)
		);
}

sf::Vector2f GameSystem::getViewportDimensions() const
{
	return camera->getViews()[0].getSize();
}

std::string GameSystem::resourcePath(const std::string & src)
{
	QDir dir(QCoreApplication::applicationDirPath());
	dir.cd("../data");
	return dir.filePath(src.c_str()).toStdString();
}

void GameSystem::loadConfig()
{
	QFile f("zoldak-config");
	if (!f.open(QIODevice::ReadOnly))
	{
		qDebug() << "Warning: failed to load config!";
		return;
	}
	
	QDataStream ds(&f);
	ds >> config;
}

void GameSystem::saveConfig() const
{
	QFile f("zoldak-config");
	if (!f.open(QIODevice::WriteOnly))
	{
		qDebug() << "Warning: failed to save config!";
		return;
	}
	
	QDataStream ds(&f);
	ds << config;
}
