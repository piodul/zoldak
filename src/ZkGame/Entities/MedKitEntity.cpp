#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "../../ZkCommon/Constants.h"
#include "../../ZkCommon/LibraryCast.h"

#include "MedKitEntity.h"
#include "SpawnerMeshEntity.h"
#include "../Renderables/BoxRenderable.h"
#include "../GameSystem.h"

using namespace Zk::Common;
using namespace Zk::Game;

MedKitEntity::MedKitEntity(sf::Vector2f pos, SpawnerMeshEntity * spawner)
	: Entity(nullptr, nullptr), spawner(spawner)
{
	b2World & world = GameSystem::getInstance()->getPhysicsSystem().getWorld();
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = lib_cast<b2Vec2>(pos);
	bodyDef.userData = (void*)this;
	b2Body * body = world.CreateBody(&bodyDef);
	
	float radius = 0.5f;
	b2PolygonShape polyShape;
	polyShape.SetAsBox(radius, radius);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	
	setBody(body);
	
	BoxRenderable * br = new BoxRenderable(
		body, "../data/medkit.png"
	);
	setRenderable(br);
}

MedKitEntity::~MedKitEntity()
{
	
}

void MedKitEntity::update(double step)
{
	
}

EntityType MedKitEntity::getType() const
{
	return EntityType::MedKitEntity;
}

void MedKitEntity::pickUp()
{
	markForDeletion();
}
