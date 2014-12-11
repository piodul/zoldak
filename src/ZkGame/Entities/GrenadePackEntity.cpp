#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "../../ZkCommon/Constants.hpp"
#include "../../ZkCommon/LibraryCast.hpp"

#include "GrenadePackEntity.hpp"
#include "SpawnerMeshEntity.hpp"
#include "../Renderables/BoxRenderable.hpp"
#include "../GameSystem.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

GrenadePackEntity::GrenadePackEntity(sf::Vector2f pos, SpawnerMeshEntity * spawner)
	:	CrateEntity(pos, sf::Vector2f(0.25f, 0.25f), "grenade-pack.png"),
		spawner(spawner)
{

}

GrenadePackEntity::~GrenadePackEntity()
{

}

void GrenadePackEntity::update(double step)
{

}

EntityType GrenadePackEntity::getType() const
{
	return EntityType::GrenadePackEntity;
}

void GrenadePackEntity::pickUp()
{
	spawner->entityPickedUp();
	markForDeletion();
}
