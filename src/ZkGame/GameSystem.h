#pragma once

#include <QtWidgets>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <list>
#include <memory>
#include <string>

#include "Config/Config.h"

#include "InputSystem.h"
#include "Physics.h"
#include "PlayerUI.h"
#include "TextureCache.h"

namespace Zk {
namespace Game {

class Entity;
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
	
	static std::string resourcePath(const std::string & src);
	
	inline InputSystem & getInputSystem()
	{ return inputSystem; }
	inline PhysicsSystem & getPhysicsSystem()
	{ return physicsSystem; }
	inline TextureCache & getTextureCache()
	{ return textureCache; }
	inline const Config & getConfig() const
	{ return config; }
	
	inline static GameSystem * getInstance()
	{ return instance; }
	
private:
	void lobbyLoop();
	
	void initializeGameLoop();
	void gameLoop();
	void cleanupGameLoop();
	
	QApplication app;
	
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;
	TextureCache textureCache;
	
	Config config;
	
	//std::vector<std::weak<PlayerEntity>> players;
	std::weak_ptr<PlayerEntity> player;
	PlayerUI playerUI;
	
	State state;
	
	sf::RenderWindow renderWindow;
	
	std::list<std::shared_ptr<Entity>> entities;
	
	Camera * camera;
	
	static GameSystem * instance;
};

}}
