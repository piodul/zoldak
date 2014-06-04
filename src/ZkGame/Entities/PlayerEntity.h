#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <memory>
#include <vector>

#include "Entity.h"
#include "../Physics.h"

namespace Zk {
namespace Game {

class Renderable;

class PlayerEntity :
	public Entity,
	public BodyCollisionListener,
	public std::enable_shared_from_this<PlayerEntity>
{
	//Może przenieść do CollisionListener?
	struct ContactInfo
	{
		b2Contact * original;
		b2Body * toucher;
		b2Vec2 normal;
		
		ContactInfo(b2Body * myBody, b2Contact * original);
		
		inline bool operator==(const ContactInfo & other) const
		{ return original == other.original; }
	};
	
	static constexpr double HORIZONTAL_VELOCITY_CAP = 5.0;
	
public:
	PlayerEntity(sf::Vector2f pos);
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

private:
	std::vector<ContactInfo> contacts;
	
	double health;
	
	double jumpCooldown;
};

}}
