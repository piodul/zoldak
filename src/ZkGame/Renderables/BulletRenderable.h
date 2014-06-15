#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "../Entities/Entity.h"
#include "../Entities/BulletEntity.h"

#include "Renderable.h"

namespace Zk {
namespace Game {

class Entity;
class PlayerEntity;

class BulletRenderable : public Renderable
{
public:
	BulletRenderable(std::weak_ptr<BulletEntity> bullet);
	virtual ~BulletRenderable();
	
	virtual void paint(sf::RenderTarget * rt);
	
private:
	std::weak_ptr<BulletEntity> bullet;
};

}}
