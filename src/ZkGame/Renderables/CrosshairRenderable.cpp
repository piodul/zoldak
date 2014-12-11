#include <SFML/Graphics.hpp>

#include "Renderable.hpp"
#include "CrosshairRenderable.hpp"
#include "SpriteRenderable.hpp"

#include "../Entities/Entity.hpp"
#include "../Entities/PlayerEntity.hpp"

#include "../GameSystem.hpp"
#include "../Player.hpp"

using namespace Zk::Game;

CrosshairRenderable::CrosshairRenderable(
	const std::string & hierarchyPath,
	std::weak_ptr<Entity> entity,
	std::weak_ptr<PlayerEntity> player
)
	: SpriteRenderable(
		hierarchyPath,
		entity,
		GameSystem::resourcePath("crosshair.png").c_str()
	)
{
	this->player = player;
}

CrosshairRenderable::~CrosshairRenderable()
{

}

bool CrosshairRenderable::visibleToPlayer(const Player & player)
{
	return this->player.lock() == player.getPlayerEntity().lock();
}