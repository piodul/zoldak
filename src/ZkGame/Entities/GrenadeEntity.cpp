#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <QDebug>

#include <cmath>

#include <array>
#include <memory>

#include "../../ZkCommon/Constants.hpp"
#include "../../ZkCommon/LibraryCast.hpp"

#include "GrenadeEntity.hpp"
#include "PlayerEntity.hpp"
#include "../Renderables/BoxRenderable.hpp"
#include "../Player.hpp"
#include "../Physics.hpp"
#include "../Game.hpp"
#include "../GameSystem.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

GrenadeEntity::GrenadeEntity(
	sf::Vector2f pos,
	sf::Vector2f velocity,
	Player & owner,
	double damage
) :
	Entity(nullptr, nullptr),
	BodyCollisionListener(nullptr),
	std::enable_shared_from_this<GrenadeEntity>(),
	owner(owner)
{
	this->damage = damage;
	countdownToExplosion = FUSE_TIME;
	canCollideWithOwner = false;

	b2World & world = Game::getInstance()->getPhysicsSystem().getWorld();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = lib_cast<b2Vec2>(pos);
	bodyDef.linearVelocity = lib_cast<b2Vec2>(velocity);
	bodyDef.bullet = true;
	bodyDef.userData = (void*)this;
	b2Body * body = world.CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = 0.20f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.5f;
	body->CreateFixture(&fixtureDef);

	setBody(body);
	setFilteringBody(body);

	BoxRenderable * br = new BoxRenderable(
		"OBJECTS",
		body, GameSystem::resourcePath("grenade-particle.png").c_str()
	);
	setRenderable(br);
}

GrenadeEntity::~GrenadeEntity()
{

}

void GrenadeEntity::registerMe()
{
	Game::getInstance()->getPhysicsSystem().registerListener(
		shared_from_this()
	);
}

void GrenadeEntity::onBeginContactEvent(b2Contact * contact)
{

}

void GrenadeEntity::onEndContactEvent(b2Contact * contact)
{
	if (!canCollideWithOwner)
	{
		ContactInfo ci(getBody(), contact);
		Entity * ent = (Entity*)ci.toucher->GetUserData();
		if (ent->getType() == EntityType::PlayerEntity)
		{
			PlayerEntity * ceEnt = (PlayerEntity*)ent;
			if (ceEnt == owner.getPlayerEntity().lock().get())
				canCollideWithOwner = true;
		}
	}
}

void GrenadeEntity::onPreSolveEvent(b2Contact * contact, const b2Manifold * oldManifold)
{
	if (!canCollideWithOwner)
	{
		ContactInfo ci(getBody(), contact);
		Entity * ent = (Entity*)ci.toucher->GetUserData();
		if (ent->getType() == EntityType::PlayerEntity)
		{
			PlayerEntity * ceEnt = (PlayerEntity*)ent;
			if (ceEnt == owner.getPlayerEntity().lock().get())
				contact->SetEnabled(false);
		}
	}
}

void GrenadeEntity::onPostSolveEvent(b2Contact * contact, const b2ContactImpulse * impulse)
{

}

void GrenadeEntity::update(double step)
{
	countdownToExplosion -= step;
	if (countdownToExplosion <= 0.0)
	{
		std::array<Player, 2> & players = Game::getInstance()->getPlayers();

		for (Player & p : players)
		{
			auto ptr = p.getPlayerEntity().lock();

			if (ptr != nullptr)
			{
				sf::Vector2f delta = ptr->getCenterPosition() - getCenterPosition();
				float distance = sqrtf(delta.x * delta.x + delta.y * delta.y);

				if (distance > RANGE)
					continue;

				distance = (RANGE - distance) / RANGE;
				double damageTotal = damage * distance * distance;

				ptr->takeDamage(damageTotal);

				if ((ptr->getHealth() == 0.0) && (&p != &owner))
					owner.reportKill();
			}
		}

		markForDeletion();
	}
}

EntityType GrenadeEntity::getType() const
{
	return EntityType::GrenadeEntity;
}
