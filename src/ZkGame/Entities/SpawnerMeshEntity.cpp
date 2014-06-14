#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <cmath>

#include <algorithm>
#include <limits>
#include <map>
#include <memory>
#include <random>

#include "../../ZkCommon/Constants.h"
#include "../../ZkCommon/LibraryCast.h"
#include "../../ZkCommon/Level.h"

#include "Entity.h"
#include "SpawnerMeshEntity.h"
#include "MedKitEntity.h"
#include "GrenadePackEntity.h"
#include "../GameSystem.h"
#include "../Renderables/Renderable.h"
#include "../Renderables/MeshRenderable.h"

using namespace Zk::Common;
using namespace Zk::Game;

static sf::Vector2f randomPointInTriangle(std::array<sf::Vector2f, 3> verts);
static sf::Vector2f randomPointInMesh(const sf::VertexArray & varr);
static float triangleArea(std::array<sf::Vector2f, 3> verts);

SpawnerMeshEntity::SpawnerMeshEntity(const LevelLayer * ll, LayerType lt)
	: Entity(nullptr, nullptr)
{
	this->ll = ll;
	this->lt = lt;
	
	cooldown = 0.0;
	
	ll->constructMesh(varr);
	
	itemCount = 0;
	if (lt == LayerType::MEDKIT_SPAWN)
		maxItemCount = Constants::MAX_MEDKITS_ON_MAP;
	else
		maxItemCount = Constants::MAX_GRENADE_PACKS_ON_MAP;
	
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
		sf::Vector2f pos = randomPointInMesh(varr);
		
		if (lt == LayerType::MEDKIT_SPAWN)
		{
			GameSystem::getInstance()->addEntity(
				std::make_shared<MedKitEntity>(pos, this)
			);
		}
		else if (lt == LayerType::GRENADES_SPAWN)
		{
			GameSystem::getInstance()->addEntity(
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

sf::Vector2f randomPointInTriangle(std::array<sf::Vector2f, 3> verts)
{
	static std::random_device rd;
	static std::default_random_engine dre(rd());
	static std::uniform_real_distribution<float> dis(0, 1);
	
	float u = dis(dre), v = dis(dre);
	
	if (u + v > 1.f)
	{
		u = 1.f - u;
		v = 1.f - v;
	}
	
	return verts[0] + u * (verts[1] - verts[0]) + v * (verts[2] - verts[0]);
}

sf::Vector2f randomPointInMesh(const sf::VertexArray & varr)
{
	static std::random_device rd;
	static std::default_random_engine dre(rd());
	
	//Liczymy pole
	float field = 0.f;
	for (int i = 0; i < (int)varr.getVertexCount(); i += 3)
		field += triangleArea({
			varr[i + 0].position,
			varr[i + 1].position,
			varr[i + 2].position
		});
	
	//Losujemy trójkąt
	std::uniform_real_distribution<float> dis(0, field);
	float t = dis(dre);
	field = 0.f;
	
	for (int i = 0; i < (int)varr.getVertexCount(); i += 3)
	{
		field += triangleArea({
			varr[i + 0].position,
			varr[i + 1].position,
			varr[i + 2].position
		});
		
		if (field >= t)
			return randomPointInTriangle({
				varr[i + 0].position,
				varr[i + 1].position,
				varr[i + 2].position
			});
	}
	
	//Justin Case
	return sf::Vector2f(0.f, 0.f);
}

float triangleArea(std::array<sf::Vector2f, 3> verts)
{
	sf::Vector2f v1 = verts[1] - verts[0];
	sf::Vector2f v2 = verts[2] - verts[0];
	
	return fabs(v1.x * v2.y - v2.x * v1.y) * 0.5f;
}
