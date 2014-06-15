#include <SFML/Graphics.hpp>

#include "Renderable.h"
#include "CrosshairRenderable.h"
#include "SpriteRenderable.h"

#include "../Entities/Entity.h"
#include "../Entities/PlayerEntity.h"

#include "../GameSystem.h"
#include "../Player.h"

using namespace Zk::Game;

CrosshairRenderable::CrosshairRenderable(
	std::weak_ptr<Entity> entity,
	std::weak_ptr<PlayerEntity> player
)
	: SpriteRenderable(entity, GameSystem::resourcePath("crosshair.png").c_str())
{
	this->player = player;
}

CrosshairRenderable::~CrosshairRenderable()
{
	
}

bool CrosshairRenderable::visibleToPlayer(std::weak_ptr<Player> player)
{
	auto ptr = player.lock();
	
	if (ptr != nullptr)
		return this->player.lock() == ptr->getPlayerEntity().lock();
	
	return false;
}