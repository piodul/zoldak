#pragma once

#include <QtWidgets>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <list>
#include <memory>

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
	
	inline InputSystem & getInputSystem()
	{ return inputSystem; }
	inline PhysicsSystem & getPhysicsSystem()
	{ return physicsSystem; }
	inline TextureCache & getTextureCache()
	{ return textureCache; }
	
	inline static GameSystem * getInstance()
	{ return instance; }
	
private:
	void lobbyLoop();
	void gameLoop();
	
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;
	TextureCache textureCache;
	
	//std::vector<std::weak<PlayerEntity>> players;
	std::weak_ptr<PlayerEntity> player;
	PlayerUI playerUI;
	
	State state;
	
	QApplication app;
	sf::RenderWindow renderWindow;
	
	std::list<std::shared_ptr<Entity>> entities;
	
	Camera * camera;
	
	static GameSystem * instance;
};

}}
