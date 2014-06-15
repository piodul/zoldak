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
#include "Game.h"
#include "InputSystem.h"
#include "Player.h"
#include "PlayerUI.h"
#include "SpawnerMesh.h"
#include "Entities/Entity.h"
#include "Entities/CrateEntity.h"
#include "Entities/PlayerEntity.h"
#include "Entities/LevelMeshEntity.h"
#include "Entities/SpawnerMeshEntity.h"
#include "Entities/PlayerTrackEntity.h"
#include "Renderables/Renderable.h"
#include "Weapons/WeaponDef.h"
#include "Weapons/Weapon.h"
#include "Camera.h"

using namespace Zk::Game;
using namespace Zk::Common;

GameSystem * GameSystem::instance = nullptr;

GameSystem::GameSystem(int argc, char ** argv) :
	app(argc, argv)
{
	state = State::Lobby;
	instance = this;
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

void GameSystem::changeState(State s)
{
	state = s;
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

void GameSystem::gameLoop()
{
	Game game(levelName);
	game.run();
}

void GameSystem::keepQtAlive(int timeForEvents)
{
	app.sendPostedEvents();
	app.processEvents(
		QEventLoop::AllEvents,
		timeForEvents
	);
}

void GameSystem::setLevelName(QString name)
{
	levelName = name;
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
