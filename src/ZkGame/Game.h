#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <QString>

#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>

#include "../ZkCommon/Level.h"

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
class GameSystem;

class Game
{
public:
	Game(QString levelName);
	~Game();
	
	void run();
	void addEntity(std::shared_ptr<Entity> ent);
	
	sf::Vector2f getViewportDimensions() const;
	
	inline PhysicsSystem & getPhysicsSystem()
	{ return physicsSystem; }
	inline std::array<Player, 2> & getPlayers()
	{ return players; }
	inline Camera * getCamera()
	{ return camera; }
	
	inline static Game * getInstance()
	{ return instance; }
	
private:
	void initializeGameLoop();
	void gameLoop();
	void removeInactiveEntities();
	void removeInactiveRenderables();
	void refreshZOrder();
	void cleanupGameLoop();
	
	sf::RenderWindow renderWindow;
	
	PhysicsSystem physicsSystem;
	
	std::list<std::shared_ptr<Entity>> entities;
	std::multimap<double, std::weak_ptr<Renderable>> renderables;
	
	std::array<Player, 2> players;
	
	Camera * camera;
	
	bool hasFocus;
	
	Common::Level level;
	
	static Game * instance;
};

}}
