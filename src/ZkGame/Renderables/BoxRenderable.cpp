#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <QtCore>
#include <QtGui>
#include <QDebug>

#include "../../ZkCommon/Constants.h"
#include "../../ZkCommon/LibraryCast.h"

#include "../GameSystem.h"
#include "../TextureCache.h"

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

	const b2Fixture * fixture = body->GetFixtureList();
	b2AABB aabb = fixture->GetAABB(0);

	texture = GameSystem::getInstance()->getTextureCache().getTexture(imgSrc);

	sf::Vector2f bodySize =
		lib_cast<sf::Vector2f>(aabb.upperBound - aabb.lowerBound);
	sf::Vector2f imageSize =
		sf::Vector2f(texture->getSize()) * (float)Constants::METERS_PER_PIXEL;

	sf::Vector2f scalingFactor = sf::Vector2f(
		bodySize.x / imageSize.x,
		bodySize.y / imageSize.y
	) * (float)Constants::METERS_PER_PIXEL;

	sprite.setTexture(*texture);
	sprite.setOrigin(sf::Vector2f(texture->getSize()) * 0.5f);
	sprite.setScale(scalingFactor);
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
