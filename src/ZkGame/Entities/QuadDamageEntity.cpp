#include "QuadDamageEntity.hpp"

#include "SpawnerMeshEntity.hpp"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "../../ZkCommon/Constants.hpp"
#include "../../ZkCommon/LibraryCast.hpp"

#include "../Renderables/BoxRenderable.hpp"
#include "../GameSystem.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

const int QuadDamageEntity::QuadTime = 5000;

QuadDamageEntity::QuadDamageEntity(sf::Vector2f pos, SpawnerMeshEntity * spawner)
	:	CrateEntity(pos, sf::Vector2f(0.25f, 0.25f), "quaddamage.png"),
		spawner(spawner)
{

}

QuadDamageEntity::~QuadDamageEntity()
{

}

void QuadDamageEntity::update(double step)
{

}

EntityType QuadDamageEntity::getType() const
{
	return EntityType::QuadDamageEntity;
}

void QuadDamageEntity::pickUp()
{
	spawner->entityPickedUp();
	markForDeletion();
}
