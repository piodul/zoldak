#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "TextureCache.hpp"

namespace Zk {
namespace Game {

class Player;

class PlayerUI
{
public:
	PlayerUI(Player & player);
	~PlayerUI();

	void paint(sf::RenderTarget * rt);

private:
	Player & player;

	sf::Font font;
	sf::Texture * healthTexture;
	sf::Texture * grenadeTexture;
	sf::Texture * ammoTexture;
};

}}
