#include <SFML/Graphics.hpp>

#include "../Entities/Entity.h"
#include "../Entities/BulletEntity.h"

#include "../GameSystem.h"

#include "BulletRenderable.h"
#include "Renderable.h"

using namespace Zk::Common;
using namespace Zk::Game;

BulletRenderable::BulletRenderable(std::weak_ptr<BulletEntity> bullet)
{
	this->bullet = bullet;
}

BulletRenderable::~BulletRenderable()
{

}

void BulletRenderable::paint(sf::RenderTarget * rt)
{
	auto ptr = bullet.lock();

	if (ptr != nullptr)
	{
		sf::Vector2f currentPosition = ptr->getCenterPosition();
		sf::Vector2f backPosition = currentPosition - ptr->getVelocity() * 0.01f;
		sf::Vertex segment[2] {
			sf::Vertex(currentPosition, sf::Color::Black),
			sf::Vertex(backPosition, sf::Color::White),
		};

		rt->draw(segment, 2, sf::Lines);
	}
}
