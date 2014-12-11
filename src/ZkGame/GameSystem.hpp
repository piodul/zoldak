#pragma once

#include <QtWidgets>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>

#include "Config/Config.hpp"

#include "InputSystem.hpp"
#include "Physics.hpp"
#include "Player.hpp"
#include "PlayerUI.hpp"
#include "TextureCache.hpp"

namespace Zk {
namespace Game {

class GameSystem
{
public:
	enum class State : int
	{
		Lobby,
		Game,
		Quit
	};

	GameSystem(int & argc, char ** argv);
	~GameSystem();

	int exec();
	void changeState(State s);

	void keepQtAlive(int timeForEvents);
	void setLevelName(QString name);

	static std::string resourcePath(const std::string & src);

	inline InputSystem & getInputSystem()
	{ return inputSystem; }
	inline TextureCache & getTextureCache()
	{ return textureCache; }
	inline const Config & getConfig() const
	{ return config; }
	inline const State getState() const
	{ return state; }

	inline static GameSystem * getInstance()
	{ return instance; }

private:
	void lobbyLoop();
	void gameLoop();

	void loadConfig();
	void saveConfig() const;

	QApplication app;

	InputSystem inputSystem;

	TextureCache textureCache;
	Config config;

	State state;
	QString levelName;

	static GameSystem * instance;
};

}}
