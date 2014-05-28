#pragma once

#include <QtWidgets>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <list>

#include "InputSystem.h"
#include "Physics.h"

namespace Zk {
namespace Game {

class Entity;

class GameSystem
{
public:
	GameSystem(int argc, char ** argv);
	~GameSystem();
	
	int exec();
	
	InputSystem & getInputSystem();
	
	inline static GameSystem * getInstance()
	{ return instance; }
	
private:
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;
	
	QApplication app;
	sf::RenderWindow renderWindow;
	
	std::list<Entity*> entities;
	
	static GameSystem * instance;
};

}}
