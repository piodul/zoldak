#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <cmath>

#include <algorithm>
#include <limits>
#include <map>
#include <memory>
#include <random>

#include "../../ZkCommon/Constants.hpp"
#include "../../ZkCommon/LibraryCast.hpp"
#include "../../ZkCommon/Level.hpp"

#include "../SpawnerMesh.hpp"

#include "Entity.hpp"
#include "SpawnerMeshEntity.hpp"
#include "MedKitEntity.hpp"
#include "GrenadePackEntity.hpp"
#include "../Game.hpp"
#include "../GameSystem.hpp"
#include "../Renderables/Renderable.hpp"
#include "../Renderables/MeshRenderable.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

SpawnerMeshEntity::SpawnerMeshEntity(const LevelLayer * ll, LayerType lt)
	: Entity(nullptr, nullptr), spawnerMesh(ll)
{
	this->lt = lt;

	cooldown = 0.0;

	itemCount = 0;
	if (lt == LayerType::MEDKIT_SPAWN)
		maxItemCount = GameSystem::getInstance()->getConfig().settingsConfig.maxMedkitsOnMap();
	else
		maxItemCount = GameSystem::getInstance()->getConfig().settingsConfig.maxGrenadePacksOnMap();

	setRenderable(nullptr);
	setBody(nullptr);
}

SpawnerMeshEntity::~SpawnerMeshEntity()
{

}

void SpawnerMeshEntity::update(double step)
{
	cooldown = std::max(0.0, cooldown - step);

	if (cooldown == 0.0 && itemCount < maxItemCount)
	{
		sf::Vector2f pos = spawnerMesh.pickSpawnLocation();

		if (lt == LayerType::MEDKIT_SPAWN)
		{
			Game::getInstance()->addEntity(
				std::make_shared<MedKitEntity>(pos, this)
			);
		}
		else if (lt == LayerType::GRENADES_SPAWN)
		{
			Game::getInstance()->addEntity(
				std::make_shared<GrenadePackEntity>(pos, this)
			);
		}

		cooldown = COOLDOWN_IN_SECONDS;
		itemCount++;
	}
}

EntityType SpawnerMeshEntity::getType() const
{
	return EntityType::SpawnerMeshEntity;
}

void SpawnerMeshEntity::entityPickedUp()
{
	itemCount--;
}
