#pragma once

#include <QtWidgets>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <list>
#include <memory>

#include "InputSystem.h"
#include "Physics.h"
#include "TextureCache.h"

namespace Zk {
namespace Game {

class Entity;
class Camera;

class GameSystem
{
public:
	GameSystem(int argc, char ** argv);
	~GameSystem();
	
	int exec();
	
	inline InputSystem & getInputSystem()
	{ return inputSystem; }
	inline PhysicsSystem & getPhysicsSystem()
	{ return physicsSystem; }
	inline TextureCache & getTextureCache()
	{ return textureCache; }
	
	inline static GameSystem * getInstance()
	{ return instance; }
	
private:
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;
	TextureCache textureCache;
	
	QApplication app;
	sf::RenderWindow renderWindow;
	
	std::list<std::shared_ptr<Entity>> entities;
	
	Camera * camera;
	
	static GameSystem * instance;
};

}}
