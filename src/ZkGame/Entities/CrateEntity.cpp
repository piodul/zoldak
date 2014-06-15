#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "../../ZkCommon/Constants.h"
#include "../../ZkCommon/LibraryCast.h"

#include "CrateEntity.h"
#include "../Renderables/BoxRenderable.h"
#include "../Game.h"
#include "../GameSystem.h"

using namespace Zk::Common;
using namespace Zk::Game;

CrateEntity::CrateEntity(sf::Vector2f pos, sf::Vector2f size, const char * imgSrc)
	: Entity(nullptr, nullptr)
{
	b2World & world = Game::getInstance()->getPhysicsSystem().getWorld();
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = lib_cast<b2Vec2>(pos);
	bodyDef.userData = (void*)this;
	b2Body * body = world.CreateBody(&bodyDef);
	
	b2PolygonShape polyShape;
	polyShape.SetAsBox(size.x, size.y);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	
	setBody(body);
	
	BoxRenderable * br = new BoxRenderable(
		body, GameSystem::resourcePath(imgSrc).c_str()
	);
	br->setZValue(-(double)LayerType::MIDGROUND);
	setRenderable(br);
}

CrateEntity::~CrateEntity()
{
	
}
