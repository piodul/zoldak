#pragma once

#include <QtWidgets>

#include <SFML/Graphics.hpp>

#include "InputSystem.h"

namespace Zk {
namespace Game {

class GameSystem
{
public:
	GameSystem(int argc, char ** argv);
	~GameSystem();
	
	int exec();
	
private:
	sf::RenderWindow renderWindow;
	sf::Texture texture;
	sf::Sprite sprite;
	
	QApplication app;
	
	InputSystem inputSystem;
};

}}
