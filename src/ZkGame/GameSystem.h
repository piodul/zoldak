#pragma once

#include <SFML/Graphics.hpp>

namespace Zk {
namespace Game {

class GameSystem
{
public:
	GameSystem();
	~GameSystem();
	
	int run();
	
private:
	sf::RenderWindow renderWindow;
	sf::Texture texture;
	sf::Sprite sprite;
};

}}
