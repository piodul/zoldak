#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "../Player.hpp"
#include "Renderable.hpp"

namespace Zk {
namespace Game {

class Entity;

class SpriteRenderable : public Renderable
{
public:
	SpriteRenderable(
		std::weak_ptr<Entity> entity,
		const char * imgSrc
	);
	virtual ~SpriteRenderable();

	virtual void paint(sf::RenderTarget * rt, const Player & viewer);

private:
	sf::Texture * texture;
	sf::Sprite sprite;

	std::weak_ptr<Entity> entity;
};

}}
