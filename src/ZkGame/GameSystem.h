#pragma once

#include <QtWidgets>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>

#include "Config/Config.h"

#include "InputSystem.h"
#include "Physics.h"
#include "Player.h"
#include "PlayerUI.h"
#include "TextureCache.h"

namespace Zk {
namespace Game {

class Entity;
class Renderable;
class PlayerEntity;
class Camera;

class GameSystem
{
public:
	enum class State : int
	{
		Lobby,
		Game,
		Quit
	};
	
	GameSystem(int argc, char ** argv);
	~GameSystem();
	
	int exec();
	void changeState(State s);
	
	void addEntity(std::shared_ptr<Entity> ent);
	
	sf::Vector2f getViewportDimensions() const;
	
	static std::string resourcePath(const std::string & src);
	
	inline InputSystem & getInputSystem()
	{ return inputSystem; }
	inline PhysicsSystem & getPhysicsSystem()
	{ return physicsSystem; }
	inline TextureCache & getTextureCache()
	{ return textureCache; }
	inline const Config & getConfig() const
	{ return config; }
	inline std::array<Player, 2> & getPlayers()
	{ return players; }
	inline Camera * getCamera()
	{ return camera; }
	
	inline static GameSystem * getInstance()
	{ return instance; }
	
private:
	void lobbyLoop();
	
	void initializeGameLoop();
	void gameLoop();
	void removeInactiveEntities();
	void removeInactiveRenderables();
	void refreshZOrder();
	void cleanupGameLoop();
	
	void loadConfig();
	void saveConfig() const;
	
	QApplication app;
	
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;
	TextureCache textureCache;
	
	Config config;
	
	std::array<Player, 2> players;
	
	State state;
	
	sf::RenderWindow renderWindow;
	
	std::list<std::shared_ptr<Entity>> entities;
	std::multimap<double, std::weak_ptr<Renderable>> renderables;
	
	Camera * camera;
	
	bool hasFocus;
	
	static GameSystem * instance;
};

}}
