#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <memory>
#include <vector>

#include "Entity.h"
#include "../Config/InputConfig.h"
#include "../Weapons/WeaponDef.h"
#include "../Weapons/Weapon.h"
#include "../InputSystem.h"
#include "../Physics.h"

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
		sf::Vector2f pos,
		const InputConfig & inputConfig,
		MouseDeviceHandle mdh,
		const WeaponDef & weaponDef
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
	void takeDamage(double damage); //Lol @ nazwa parametru
	
	inline int getGrenadeCount() const
	{ return grenadeCount; }
	
	inline const Weapon & getWeapon() const
	{ return weapon; }

private:
	void pickUpMedKit();
	void pickUpGrenadePack();
	
	std::vector<ContactInfo> contacts;
	
	double health;
	int grenadeCount;
	
	double jumpCooldown;
	Weapon weapon;
	MouseDeviceHandle mouseDevice;
	const InputConfig & inputConfig;
	
	std::weak_ptr<CrosshairEntity> crosshair;
};

}}
