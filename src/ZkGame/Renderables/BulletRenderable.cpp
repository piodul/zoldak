#include <SFML/Graphics.hpp>

#include "../Entities/Entity.hpp"
#include "../Entities/BulletEntity.hpp"

#include "../GameSystem.hpp"
#include "../Player.hpp"

#include "BulletRenderable.hpp"
#include "Renderable.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

BulletRenderable::BulletRenderable(
	const std::string & hierarchyPath,
	std::weak_ptr<BulletEntity> bullet
)
	: Renderable(hierarchyPath)
{
	this->bullet = bullet;
}

BulletRenderable::~BulletRenderable()
{

}

void BulletRenderable::paint(sf::RenderTarget * rt, const Player & viewer)
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
