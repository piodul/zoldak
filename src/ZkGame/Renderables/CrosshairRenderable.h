#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "Renderable.h"
#include "SpriteRenderable.h"

namespace Zk {
namespace Game {

class Entity;
class PlayerEntity;

class CrosshairRenderable : public SpriteRenderable
{
public:
	CrosshairRenderable(
		std::weak_ptr<Entity> entity,
		std::weak_ptr<PlayerEntity> player
	);
	virtual ~CrosshairRenderable();

	virtual bool visibleToPlayer(const Player & player);

private:
	sf::Texture * texture;
	sf::Sprite sprite;

	std::weak_ptr<PlayerEntity> player;
};

}}
