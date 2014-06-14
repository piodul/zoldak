#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>

#include <cmath>

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include <QtCore>
#include <QDebug>

#include "../../ZkCommon/Constants.h"
#include "../../ZkCommon/LibraryCast.h"

#include "PlayerEntity.h"
#include "MedKitEntity.h"
#include "../Renderables/BoxRenderable.h"
#include "../GameSystem.h"

using namespace Zk::Common;
using namespace Zk::Game;

PlayerEntity::ContactInfo::ContactInfo(b2Body * myBody, b2Contact * original)
{
	this->original = original;
	
	b2WorldManifold worldManifold;
	original->GetWorldManifold(&worldManifold);
	
	if (original->GetFixtureA()->GetBody() == myBody)
	{
		normal = worldManifold.normal;
		toucher = original->GetFixtureB()->GetBody();
	}
	else
	{
		normal = -worldManifold.normal;
		toucher = original->GetFixtureA()->GetBody();
	}
}

PlayerEntity::PlayerEntity(sf::Vector2f pos) :
	Entity(nullptr, nullptr),
	BodyCollisionListener(nullptr),
	std::enable_shared_from_this<PlayerEntity>()
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
	fixtureDef.friction = 0.6f;
	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);
	
	setBody(body);
	setFilteringBody(body);
	
	BoxRenderable * br = new BoxRenderable(
		body, "../data/grenade-pack.png"
	);
	setRenderable(br);
	
	jumpCooldown = 0.0;
	
	health = 0.0;
	grenadeCount = 3;
}

PlayerEntity::~PlayerEntity()
{
	
}

void PlayerEntity::registerMe()
{
	GameSystem::getInstance()->getPhysicsSystem().registerListener(
		shared_from_this()
	);
}

void PlayerEntity::onBeginContactEvent(b2Contact * contact)
{
	ContactInfo ci(getBody(), contact);
	contacts.push_back(ci);
	Entity * entToucher = (Entity*)ci.toucher->GetUserData();
	//qDebug() << "Toucher" << entToucher;
	//qDebug() << "Toucher type:" << (int)entToucher->getType();
	//qDebug() << "Player is being touched by" << contacts.size() << "touchers";
}

void PlayerEntity::onEndContactEvent(b2Contact * contact)
{
	//using namespace std::rel_ops;
	ContactInfo ci(getBody(), contact);
	contacts.erase(std::find(contacts.begin(), contacts.end(), ci));
	//qDebug() << "Player is being touched by" << contacts.size() << "touchers";
}

void PlayerEntity::onPreSolveEvent(b2Contact * contact, const b2Manifold * oldManifold)
{
	ContactInfo ci(getBody(), contact);
	Entity * ent = (Entity*)ci.toucher->GetUserData();
	if (ent->getType() == EntityType::MedKitEntity)
	{
		MedKitEntity * ceEnt = (MedKitEntity*)ent;
		ceEnt->pickUp();
		contact->SetEnabled(false);
		qDebug() << "pickup";
		
		health += 30.0;
	}
}

void PlayerEntity::onPostSolveEvent(b2Contact * contact, const b2ContactImpulse * impulse)
{
	
}

void PlayerEntity::update(double step)
{
	const b2Vec2 runAcceleration(25.f, 0.f);
	const b2Vec2 strafeAcceleration(10.f, 0.f);
	
	bool isStanding = false;
	bool isRunning = false;
	
	b2Vec2 groundNormal(0.f, 0.f);
	
	//Sprawdźmy, czy stoimy na twardym gruncie
	{
		for (const ContactInfo & ci : contacts)
		{
			Entity * ent = (Entity*)ci.toucher->GetUserData();
			
			if (ent->getType() == EntityType::LevelMeshEntity && ci.normal.y > 0.05f)
				groundNormal += ci.normal;
		}
		
		//qDebug() << lib_cast<QPointF>(groundNormal);
		
		if (groundNormal.LengthSquared() > 0.f)
			isStanding = true;
	}
	
	jumpCooldown = std::max(0.0, jumpCooldown - step);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (getBody()->GetLinearVelocity().x > -HORIZONTAL_VELOCITY_CAP)
			getBody()->ApplyForceToCenter(
				isStanding ? -runAcceleration : -strafeAcceleration,
				true
			);
		
		if (isStanding)
			isRunning = !isRunning;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (getBody()->GetLinearVelocity().x < HORIZONTAL_VELOCITY_CAP)
			getBody()->ApplyForceToCenter(
				isStanding ? runAcceleration : strafeAcceleration,
				true
			);
		
		if (isStanding)
			isRunning = !isRunning;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && jumpCooldown == 0.f)
	{
		if (isStanding)
		{
			float scale = -7.5f / groundNormal.Length();
			groundNormal.x *= scale;
			groundNormal.y *= scale;
			
			//qDebug() << "Jump!";
			getBody()->ApplyLinearImpulse(
				groundNormal, b2Vec2(0.f, 0.f), true
			);
			
			jumpCooldown = 0.25;
			isStanding = false;
		}
	}
	
	//Jeśli nie biegniemy i jesteśmy na ziemi, powinniśmy szybko spowolnić nasz bieg
	if (isStanding && !isRunning)
	{
		b2Vec2 velocity = getBody()->GetLinearVelocity();
		//qDebug() << "Speed reset";
		getBody()->SetLinearVelocity(b2Vec2(0.f, velocity.y));
	}
	
	//if (isStanding)
	//	qDebug() << "I'm standing";
	//if (isRunning)
	//	qDebug() << "I'm running";
}

EntityType PlayerEntity::getType() const
{
	return EntityType::PlayerEntity;
}

void PlayerEntity::takeDamage(double damage)
{
	
}
