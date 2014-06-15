#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "Renderable.h"
#include "SpriteRenderable.h"

namespace Zk {
namespace Game {

class PlayerEntity;

class CrosshairRenderable : public SpriteRenderable
{
public:
	CrosshairRenderable(std::weak_ptr<PlayerEntity> player);
	virtual ~CrosshairRenderable();
	
	virtual bool visibleToPlayer(std::weak_ptr<Player> player);
	
private:
	sf::Texture * texture;
	sf::Sprite sprite;
	
	std::weak_ptr<PlayerEntity> player;
};

}}
