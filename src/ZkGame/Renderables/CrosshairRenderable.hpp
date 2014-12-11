#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

#include "Renderable.hpp"
#include "SpriteRenderable.hpp"

namespace Zk {
namespace Game {

class Entity;
class PlayerEntity;

class CrosshairRenderable : public SpriteRenderable
{
public:
	CrosshairRenderable(
		const std::string & hierarchyPath,
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
