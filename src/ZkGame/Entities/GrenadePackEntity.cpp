#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "../../ZkCommon/Constants.h"
#include "../../ZkCommon/LibraryCast.h"

#include "GrenadePackEntity.h"
#include "SpawnerMeshEntity.h"
#include "../Renderables/BoxRenderable.h"
#include "../GameSystem.h"

using namespace Zk::Common;
using namespace Zk::Game;

GrenadePackEntity::GrenadePackEntity(sf::Vector2f pos, SpawnerMeshEntity * spawner)
	:	CrateEntity(pos, sf::Vector2f(0.25f, 0.25f), "../data/grenade-pack.png"),
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
