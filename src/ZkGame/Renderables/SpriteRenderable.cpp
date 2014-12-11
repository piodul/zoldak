#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "../../ZkCommon/Constants.hpp"
#include "../../ZkCommon/LibraryCast.hpp"

#include "../Entities/Entity.hpp"

#include "../GameSystem.hpp"
#include "../TextureCache.hpp"
#include "../Player.hpp"

#include "SpriteRenderable.hpp"
#include "Renderable.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

SpriteRenderable::SpriteRenderable(
	const std::string & hierarchyPath,
	std::weak_ptr<Entity> entity,
	const char * imgSrc
)
	: Renderable(hierarchyPath)
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

void SpriteRenderable::paint(sf::RenderTarget * rt, const Player & viewer)
{
	auto ptr = entity.lock();

	if (ptr != nullptr)
	{
		sprite.setPosition(ptr->getCenterPosition());
		rt->draw(sprite);
	}
}
