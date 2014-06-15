#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "Renderable.h"

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
	
	virtual void paint(sf::RenderTarget * rt);
	
private:
	sf::Texture * texture;
	sf::Sprite sprite;
	
	std::weak_ptr<Entity> entity;
};

}}
