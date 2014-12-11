#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <QDebug>

#include <memory>

#include "../../ZkCommon/Constants.hpp"
#include "../../ZkCommon/LibraryCast.hpp"

#include "BulletEntity.hpp"
#include "PlayerEntity.hpp"
#include "../Renderables/BulletRenderable.hpp"
#include "../Player.hpp"
#include "../Physics.hpp"
#include "../Game.hpp"
#include "../GameSystem.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

BulletEntity::BulletEntity(
	sf::Vector2f pos,
	sf::Vector2f velocity,
	Player & owner,
	double damage
) :
	Entity(nullptr, nullptr),
	BodyCollisionListener(nullptr),
	std::enable_shared_from_this<BulletEntity>(),
	owner(owner)
{
	this->damage = damage;

	b2World & world = Game::getInstance()->getPhysicsSystem().getWorld();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = lib_cast<b2Vec2>(pos);
	bodyDef.linearVelocity = lib_cast<b2Vec2>(velocity);
	bodyDef.bullet = true;
	bodyDef.userData = (void*)this;
	b2Body * body = world.CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = 0.05f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 2.0f;
	fixtureDef.friction = 1.0f;
	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);

	setBody(body);
	setFilteringBody(body);
}

BulletEntity::~BulletEntity()
{

}

void BulletEntity::registerMe()
{
	Game::getInstance()->getPhysicsSystem().registerListener(
		shared_from_this()
	);

	BulletRenderable * br = new BulletRenderable(
		"OBJECTS",
		shared_from_this()
	);

	setRenderable(br);
}

void BulletEntity::onBeginContactEvent(b2Contact * contact)
{

}

void BulletEntity::onEndContactEvent(b2Contact * contact)
{

}

void BulletEntity::onPreSolveEvent(b2Contact * contact, const b2Manifold * oldManifold)
{
	ContactInfo ci(getBody(), contact);
	Entity * ent = (Entity*)ci.toucher->GetUserData();
	if (ent->getType() == EntityType::PlayerEntity)
	{
		PlayerEntity * ceEnt = (PlayerEntity*)ent;
		if (ceEnt == owner.getPlayerEntity().lock().get())
		{
			//Samego siebie nie krzywdzimy
			contact->SetEnabled(false);
			return;
		}
		else
		{
			//Innego gracza owszem
			if (ceEnt->getHealth() > 0.0)
			{
				ceEnt->takeDamage(damage);
				if (ceEnt->getHealth() == 0.0)
					owner.reportKill();
			}
		}
	}

	//Przy uderzeniu w cokolwiek innego niż gracz,
	//który nas wystrzelił, giniemy
	markForDeletion();
}

void BulletEntity::onPostSolveEvent(b2Contact * contact, const b2ContactImpulse * impulse)
{

}

void BulletEntity::update(double step)
{

}

EntityType BulletEntity::getType() const
{
	return EntityType::BulletEntity;
}

sf::Vector2f BulletEntity::getVelocity() const
{
	return lib_cast<sf::Vector2f>(getBody()->GetLinearVelocity());
}
