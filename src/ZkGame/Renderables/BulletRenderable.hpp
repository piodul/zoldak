#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

#include "../Entities/Entity.hpp"
#include "../Entities/BulletEntity.hpp"

#include "../Player.hpp"
#include "Renderable.hpp"

namespace Zk {
namespace Game {

class Entity;
class PlayerEntity;

class BulletRenderable : public Renderable
{
public:
	BulletRenderable(
		const std::string & hierarchyPath,
		std::weak_ptr<BulletEntity> bullet
	);
	virtual ~BulletRenderable();

	virtual void paint(sf::RenderTarget * rt, const Player & viewer);

private:
	std::weak_ptr<BulletEntity> bullet;
};

}}
