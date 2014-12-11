#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <memory>
#include <vector>

#include "Entity.hpp"
#include "../Config/InputConfig.hpp"
#include "../Weapons/WeaponDef.hpp"
#include "../Weapons/Weapon.hpp"
#include "../InputSystem.hpp"
#include "../Physics.hpp"
#include "../Player.hpp"

namespace Zk {
namespace Game {

class Renderable;
class CrosshairEntity;

class PlayerEntity :
	public Entity,
	public BodyCollisionListener,
	public std::enable_shared_from_this<PlayerEntity>
{
	static constexpr double HORIZONTAL_VELOCITY_CAP = 5.0;

public:
	static constexpr double MAX_HP = 100.0;
	static const int MAX_GRENADES = 5;

	PlayerEntity(
		Player & player,
		sf::Vector2f pos,
		const InputConfig & inputConfig
	);
	virtual ~PlayerEntity();

	void registerMe();

	virtual void onBeginContactEvent(b2Contact * contact) override;
	virtual void onEndContactEvent(b2Contact * contact) override;
	virtual void onPreSolveEvent(b2Contact * contact, const b2Manifold * oldManifold) override;
	virtual void onPostSolveEvent(b2Contact * contact, const b2ContactImpulse * impulse) override;

	virtual void update(double step);
	virtual EntityType getType() const override;

	inline double getHealth() const
	{ return health; }
	void takeDamage(double damage);

	int getGrenadeCount() const;

	inline const Weapon & getWeapon() const
	{ return weapon; }

	inline std::weak_ptr<CrosshairEntity> getCrosshairEntity() const
	{ return crosshair; }

private:
	void pickUpMedKit();
	void pickUpGrenadePack();

	std::vector<ContactInfo> contacts;

	double health;

	double jumpCooldown;
	Weapon weapon;
	Weapon grenadeWeapon;
	const InputConfig & inputConfig;

	Player & player;
	std::weak_ptr<CrosshairEntity> crosshair;
};

}}
