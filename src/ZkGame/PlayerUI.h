#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "Entities/PlayerEntity.h"
#include "TextureCache.h"

namespace Zk {
namespace Game {

class PlayerUI
{
public:
	PlayerUI(TextureCache & tc);
	~PlayerUI();
	
	void paint(
		sf::RenderTarget * rt,
		std::weak_ptr<PlayerEntity> pe,
		sf::FloatRect area
	);
	
private:
	sf::Font font;
	sf::Texture * healthTexture;
	sf::Texture * grenadeTexture;
	sf::Texture * ammoTexture;
};

}}
