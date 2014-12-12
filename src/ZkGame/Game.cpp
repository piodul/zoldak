#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <Box2D/Box2D.h>
#include "../ManyMouse/manymouse.h"

#include <QtWidgets>
#include <QtGui>

#include <list>
#include <memory>

#include "../ZkCommon/Constants.hpp"
#include "../ZkCommon/Level.hpp"

#include "Config/Config.hpp"
#include "Config/GraphicsConfig.hpp"
#include "Lobby/LobbyWindow.hpp"

#include "Game.hpp"
#include "GameSystem.hpp"
#include "InputSystem.hpp"
#include "Player.hpp"
#include "PlayerUI.hpp"
#include "SpawnerMesh.hpp"
#include "Entities/Entity.hpp"
#include "Entities/CrateEntity.hpp"
#include "Entities/PlayerEntity.hpp"
#include "Entities/LevelMeshEntity.hpp"
#include "Entities/SpawnerMeshEntity.hpp"
#include "Entities/PlayerTrackEntity.hpp"
#include "Renderables/Renderable.hpp"
#include "Renderables/GraphicsLayers/GraphicsLayer.hpp"
#include "Renderables/GraphicsLayers/ContainerGraphicsLayer.hpp"
#include "Renderables/GraphicsLayers/FovGraphicsLayer.hpp"
#include "Weapons/WeaponDef.hpp"
#include "Weapons/Weapon.hpp"
#include "Camera.hpp"


using namespace Zk::Common;
using namespace Zk::Game;

static constexpr double MILLIS_PER_FRAME = 1.0 / 60.0;

Game * Game::instance = nullptr;

Game::Game(QString levelName) :
	physicsSystem(),
	rootLayer("", ""),
	players{
		Player(0),
		Player(1)
	}
{
	const Config & config = GameSystem::getInstance()->getConfig();

	instance = this;
	hasFocus = true;

	QFile f(GameSystem::resourcePath(levelName.toStdString()).c_str());
	if (!f.open(QIODevice::ReadOnly))
		qDebug() << "Failed to open level";
	else
	{
		QDataStream ds(&f);
		ds >> level;
	}

	const LevelLayer * fovObscurant = level.getLayers()[(int)LayerType::MIDGROUND];
	sf::VertexArray verts;
	fovObscurant->constructOutline(verts);

	objectsLayer = std::make_shared<FovGraphicsLayer>(verts, "", "OBJECTS");
	objectsLayer->setFovEffectEnabled(config.settingsConfig.enabledFovEffect());

	graphicsLayers = {
		std::make_shared<ContainerGraphicsLayer>("", "BACKGROUND"),
		objectsLayer,
		std::make_shared<ContainerGraphicsLayer>("", "MIDGROUND"),
		std::make_shared<ContainerGraphicsLayer>("", "FOREGROUND"),
		std::make_shared<ContainerGraphicsLayer>("", "UI")
	};

	for (auto p : graphicsLayers)
		rootLayer.addChild(p);
}

Game::~Game()
{

}

void Game::run()
{
	initializeGameLoop();
	gameLoop();
	cleanupGameLoop();
}

void Game::addEntity(std::shared_ptr<Entity> ent)
{
	entities.push_back(ent);

	std::weak_ptr<Renderable> r = ent->getRenderable();
	auto ptr = r.lock();

	if (ptr != nullptr)
		rootLayer.addChild(ptr);
}

sf::Vector2f Game::getViewportDimensions() const
{
	return camera->getViews()[0].getSize();
}

void Game::initializeGameLoop()
{
	const Config & config = GameSystem::getInstance()->getConfig();

	{
		sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;
		if (config.graphicsConfig.fullscreen)
			style |= sf::Style::Fullscreen;

		renderWindow.create(
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
			GameSystem::resourcePath("grenade.png"))
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

	addEntity(
		std::make_shared<LevelMeshEntity>(
			level.getLayers()[(int)LayerType::FOREGROUND],
			LayerType::FOREGROUND
		)
	);

	addEntity(
		std::make_shared<LevelMeshEntity>(
			level.getLayers()[(int)LayerType::MIDGROUND],
			LayerType::MIDGROUND
		)
	);

	addEntity(
		std::make_shared<LevelMeshEntity>(
			level.getLayers()[(int)LayerType::BACKGROUND],
			LayerType::BACKGROUND
		)
	);

	addEntity(
		std::make_shared<SpawnerMeshEntity>(
			level.getLayers()[(int)LayerType::MEDKIT_SPAWN],
			LayerType::MEDKIT_SPAWN
		)
	);

	addEntity(
		std::make_shared<SpawnerMeshEntity>(
			level.getLayers()[(int)LayerType::GRENADES_SPAWN],
			LayerType::GRENADES_SPAWN
		)
	);

	{
		players[0].setSpawnerMesh(SpawnerMesh(
			level.getLayers()[(int)LayerType::PLAYER_A_SPAWN]
		));
		players[0].setInputConfig(config.playerInputConfig[0]);

		players[1].setSpawnerMesh(SpawnerMesh(
			level.getLayers()[(int)LayerType::PLAYER_B_SPAWN]
		));
		players[1].setInputConfig(config.playerInputConfig[1]);

	}

	auto track = std::make_shared<PlayerTrackEntity>(0);
	auto track2 = std::make_shared<PlayerTrackEntity>(1);
	entities.push_back(track);
	entities.push_back(track2);

	camera = new SplitScreenCamera({ track, track2 });
}

void Game::gameLoop()
{
	sf::Vector2f position;
	sf::Clock beat;

	int timeForEvents = 0;

	//renderWindow.setFramerateLimit(60);

	while (GameSystem::getInstance()->getState() == GameSystem::State::Game)
	{
		//Wykonaj Qt-ową część programu
		sf::Time frameStart = beat.getElapsedTime();

		GameSystem::getInstance()->keepQtAlive(timeForEvents);

		sf::Time qtLoopFinished = beat.getElapsedTime();

		//Eventy SFML-a
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				GameSystem::getInstance()->changeState(
					GameSystem::State::Lobby
				);
			}
			else if (event.type == sf::Event::GainedFocus)
				hasFocus = true;
			else if (event.type == sf::Event::MouseButtonPressed)
				hasFocus = true;
			else if (event.type == sf::Event::LostFocus)
				hasFocus = false;
		}

		//Eventy ManyMouse'a
		GameSystem::getInstance()->getInputSystem().pollInput();

		//Fizyka
		physicsSystem.simulate(MILLIS_PER_FRAME);

		//Niektóre jednostki mogą chcieć skorzystać z widoków kamery
		camera->setupViews();

		players[0].update(MILLIS_PER_FRAME);
		players[1].update(MILLIS_PER_FRAME);

		//Update
		for (std::shared_ptr<Entity> ent : entities)
			ent->update(MILLIS_PER_FRAME);

		//Render
		renderWindow.clear(sf::Color::White);

		std::vector<sf::View> views = camera->getViews();

		int viewid = 0;
		for (sf::View view : views)
		{
			renderWindow.setView(view);
			rootLayer.paint(&renderWindow, players[viewid]);

			//Teraz rysujemy UI
			players[viewid].paintUI(&renderWindow);

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
		static const sf::Int32 millisPerFrame = (int)(MILLIS_PER_FRAME * 1000.0);
		timeForEvents =
			millisPerFrame - (qtLoopFinished - frameStart).asMilliseconds();

		//Śpimy, bo glFinish() robi aktywne czekanie
		int timeToSleep = millisPerFrame - (frameEnd - frameStart).asMilliseconds();
		timeToSleep = std::max(timeToSleep - 3, 0);
		QThread::currentThread()->msleep(timeToSleep);

		//Mój komputer wymaga tej funkcji, aby vsync działał poprawnie
		//Zasraniec robi aktywne czekanie, though
		glFinish();

		//Jeśli wciśnięty jest klawisz escape, wychodzimy z gry
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			GameSystem::getInstance()->changeState(
				GameSystem::State::Lobby
			);
	}
}

void Game::removeInactiveEntities()
{
	entities.remove_if(
		[](const std::shared_ptr<Entity> & ent) -> bool
		{
			return ent->wantsToBeDeleted();
		}
	);
}

void Game::cleanupGameLoop()
{
	entities.clear();
	delete camera;
}
