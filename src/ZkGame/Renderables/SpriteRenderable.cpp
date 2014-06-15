#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <QDebug>

#include "../../ZkCommon/Constants.h"
#include "../../ZkCommon/LibraryCast.h"

#include "../Entities/Entity.h"

#include "../GameSystem.h"
#include "../TextureCache.h"

#include "SpriteRenderable.h"
#include "Renderable.h"

using namespace Zk::Common;
using namespace Zk::Game;

SpriteRenderable::SpriteRenderable(
	std::weak_ptr<Entity> entity,
	const char * imgSrc
)
{
	this->entity = entity;
	
	texture = GameSystem::getInstance()->getTextureCache().getTexture(imgSrc);
	
	sprite.setTexture(*texture);
	sprite.setOrigin(sf::Vector2f(texture->getSize()) * 0.5f);
	sprite.setScale(
		Constants::METERS_PER_PIXEL,
		Constants::METERS_PER_PIXEL
	);
}

SpriteRenderable::~SpriteRenderable()
{
	
}

void SpriteRenderable::paint(sf::RenderTarget * rt)
{
	auto ptr = entity.lock();
	
	if (ptr != nullptr)
	{
		sprite.setPosition(ptr->getCenterPosition());
		rt->draw(sprite);
	}
}
