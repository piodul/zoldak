#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>

#include <cmath>

#include <algorithm>
#include <memory>
#include <utility>

#include <QtCore>
#include <QDebug>

#include "../../ZkCommon/Constants.hpp"
#include "../../ZkCommon/LibraryCast.hpp"

#include "PlayerEntity.hpp"
#include "MedKitEntity.hpp"
#include "GrenadePackEntity.hpp"
#include "CrosshairEntity.hpp"
#include "../Config/InputConfig.hpp"
#include "../Config/PlayerAction.hpp"
#include "../Config/InputAction.hpp"
#include "../Renderables/BoxRenderable.hpp"
#include "../Weapons/WeaponDef.hpp"
#include "../Weapons/Weapon.hpp"
#include "../Game.hpp"
#include "../GameSystem.hpp"
#include "../InputSystem.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

static const WeaponDef mainWeaponDef {
	7.5,	//obrażenia od jednego strzału
	100.0,	//prędkość wylotowa
	0.05,	//czas do następnego wystrzału
	3.0,	//czas przzeładowania
	30,		//rozmiar magazynka
	WeaponDef::ParticleType::BULLET
};

static const WeaponDef grenadeDef {
	100.0,	//obrażenia od jednego strzału
	10.0,	//prędkość wylotowa
	0.5,	//czas do następnego strzału
	0.0,	//czas przeładowania (tutaj nieistotny)
	5,		//rozmiar magazynka
	WeaponDef::ParticleType::GRENADE
};

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

PlayerEntity::PlayerEntity(
	Player & player,
	sf::Vector2f pos,
	const InputConfig & inputConfig
) :
	Entity(nullptr, nullptr),
	BodyCollisionListener(nullptr),
	std::enable_shared_from_this<PlayerEntity>(),
	weapon(mainWeaponDef, player),
	grenadeWeapon(grenadeDef, player),
	inputConfig(inputConfig),
	player(player)
{
	b2World & world = Game::getInstance()->getPhysicsSystem().getWorld();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = lib_cast<b2Vec2>(pos);
	bodyDef.userData = (void*)this;
	b2Body * body = world.CreateBody(&bodyDef);

	float bodyWidth = 24.f / 64.f;
	float bodyHeight = 40.f / 64.f;
	b2PolygonShape polyShape;
	polyShape.SetAsBox(bodyWidth, bodyHeight);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.6f;
	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);

	setBody(body);
	setFilteringBody(body);

	std::string characterPath;
	if (player.getID())
		characterPath = "soldier-A.png";
	else
		characterPath = "soldier-B.png";

	BoxRenderable * br = new BoxRenderable(
		"OBJECTS",
		body, GameSystem::resourcePath(characterPath).c_str()
	);
	setRenderable(br);

	jumpCooldown = 0.0;

	health = MAX_HP;
}

PlayerEntity::~PlayerEntity()
{

}

void PlayerEntity::registerMe()
{
	Game::getInstance()->getPhysicsSystem().registerListener(
		shared_from_this()
	);

	auto crosshair = std::make_shared<CrosshairEntity>(
		shared_from_this(), inputConfig.mouseDevice
	);

	crosshair->registerMe();
	Game::getInstance()->addEntity(crosshair);
	this->crosshair = crosshair;
}

void PlayerEntity::onBeginContactEvent(b2Contact * contact)
{
	ContactInfo ci(getBody(), contact);
	contacts.push_back(ci);
}

void PlayerEntity::onEndContactEvent(b2Contact * contact)
{
	ContactInfo ci(getBody(), contact);
	contacts.erase(std::find(contacts.begin(), contacts.end(), ci));
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

		pickUpMedKit();
	}
	else if (ent->getType() == EntityType::GrenadePackEntity)
	{
		GrenadePackEntity * ceEnt = (GrenadePackEntity*)ent;
		ceEnt->pickUp();
		contact->SetEnabled(false);

		pickUpGrenadePack();
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

		if (groundNormal.LengthSquared() > 0.f)
			isStanding = true;
	}

	jumpCooldown = std::max(0.0, jumpCooldown - step);

	if (inputConfig.isActionTriggered(PlayerAction::GoLeft))
	{
		if (getBody()->GetLinearVelocity().x > -HORIZONTAL_VELOCITY_CAP)
			getBody()->ApplyForceToCenter(
				isStanding ? -runAcceleration : -strafeAcceleration,
				true
			);

		if (isStanding)
			isRunning = !isRunning;
	}

	if (inputConfig.isActionTriggered(PlayerAction::GoRight))
	{
		if (getBody()->GetLinearVelocity().x < HORIZONTAL_VELOCITY_CAP)
			getBody()->ApplyForceToCenter(
				isStanding ? runAcceleration : strafeAcceleration,
				true
			);

		if (isStanding)
			isRunning = !isRunning;
	}

	if (inputConfig.isActionTriggered(PlayerAction::Jump)
		&& jumpCooldown == 0.f)
	{
		if (isStanding)
		{
			float scale = -7.5f / groundNormal.Length();
			groundNormal.x *= scale;
			groundNormal.y *= scale;

			getBody()->ApplyLinearImpulse(
				groundNormal, b2Vec2(0.f, 0.f), true
			);

			jumpCooldown = 0.25;
			isStanding = false;
		}
	}

	//Jeśli nie biegniemy i jesteśmy na ziemi, powinniśmy szybko spowolnić nasz bieg
	if (isStanding && !isRunning && jumpCooldown == 0.f)
		getBody()->SetLinearVelocity(b2Vec2(0.f, 0.f));

	//Aktualizacja broni
	sf::Vector2f direction =
		crosshair.lock()->getCenterPosition() - getCenterPosition();

	weapon.update(
		step, direction, inputConfig.isActionTriggered(PlayerAction::Shoot)
	);

	//Aktualizacja granatów
	grenadeWeapon.update(
		step, direction, inputConfig.isActionTriggered(PlayerAction::ThrowGrenade)
	);
}

EntityType PlayerEntity::getType() const
{
	return EntityType::PlayerEntity;
}

void PlayerEntity::takeDamage(double damage)
{
	if (health == 0.0)
		return;

	health = std::max(0.0, health - damage);

	if (health == 0.0)
	{
		player.reportDeath();
		markForDeletion();
	}
}

int PlayerEntity::getGrenadeCount() const
{
	return grenadeWeapon.getAmmoCount();
}

void PlayerEntity::pickUpMedKit()
{
	health += MedKitEntity::HP_PER_MEDKIT;
	if (health > MAX_HP)
		health = MAX_HP;
}

void PlayerEntity::pickUpGrenadePack()
{
	grenadeWeapon.loadAmmo(1);
}
