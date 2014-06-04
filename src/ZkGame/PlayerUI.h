#pragma once

#include <SFML/Graphics.hpp>

#include "Entities/PlayerEntity.h"

namespace Zk {
namespace Game {

class PlayerUI
{
public:
	PlayerUI();
	~PlayerUI();
	
	void paint(sf::RenderTarget * rt, sf::FloatRect area);
	
private:
	sf::Font font;
};

}}
