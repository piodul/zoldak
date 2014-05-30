#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "../../ZkCommon/Constants.h"
#include "../../ZkCommon/LibraryCast.h"

#include "BoxRenderable.h"
#include "Renderable.h"

using namespace Zk::Common;
using namespace Zk::Game;

BoxRenderable::BoxRenderable(
	const b2Body * body,
	const char * imgSrc
)
{
	this->body = body;
	
	texture.loadFromFile(imgSrc);
	sprite.setTexture(texture);
	sprite.setOrigin(32.f, 32.f);
	sprite.setScale(Constants::METERS_PER_PIXEL, Constants::METERS_PER_PIXEL);
}

BoxRenderable::~BoxRenderable()
{
	
}

void BoxRenderable::paint(sf::RenderTarget * rt)
{
	sprite.setPosition(lib_cast<sf::Vector2f>(body->GetPosition()));
	
	float angle = body->GetAngle() * 180.f / b2_pi;
	sprite.setRotation(angle);
	
	rt->draw(sprite);
}
