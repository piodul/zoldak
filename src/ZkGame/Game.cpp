#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "../ManyMouse/manymouse.h"

#include "Game.h"
#include "GameSystem.h"

using namespace Zk::Game;

Game::Game(GameSystem & gameSys)
	: gameSys(gameSys)
{
	
}

Game::~Game()
{
	
}
