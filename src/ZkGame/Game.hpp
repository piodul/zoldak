#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <QString>

#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>

#include "../ZkCommon/Level.hpp"

#include "Config/Config.hpp"

#include "Renderables/GraphicsLayers/ContainerGraphicsLayer.hpp"
#include "Renderables/GraphicsLayers/FovGraphicsLayer.hpp"

#include "InputSystem.hpp"
#include "Physics.hpp"
#include "Player.hpp"
#include "PlayerUI.hpp"
#include "TextureCache.hpp"

namespace Zk {
namespace Game {

class Entity;
class Renderable;
class GraphicsLayer;
class FovGraphicsLayer;
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
	void cleanupGameLoop();

	sf::RenderWindow renderWindow;

	PhysicsSystem physicsSystem;

	std::list<std::shared_ptr<Entity>> entities;
	ContainerGraphicsLayer rootLayer;

	std::vector<std::shared_ptr<GraphicsLayer>> graphicsLayers;
	std::shared_ptr<FovGraphicsLayer> objectsLayer;

	std::array<Player, 2> players;

	Camera * camera;

	bool hasFocus;

	Common::Level level;

	static Game * instance;
};

}}
