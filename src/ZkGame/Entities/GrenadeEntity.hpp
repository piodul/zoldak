#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <memory>

#include "Entity.hpp"
#include "PlayerEntity.hpp"

namespace Zk {
namespace Game {

class Renderable;

class GrenadeEntity :
	public Entity,
	public BodyCollisionListener,
	public std::enable_shared_from_this<GrenadeEntity>
{
public:
	GrenadeEntity(
		sf::Vector2f pos,
		sf::Vector2f velocity,
		Player & owner,
		double damage
	);
	virtual ~GrenadeEntity();

	void registerMe();

	virtual void onBeginContactEvent(b2Contact * contact) override;
	virtual void onEndContactEvent(b2Contact * contact) override;
	virtual void onPreSolveEvent(b2Contact * contact, const b2Manifold * oldManifold) override;
	virtual void onPostSolveEvent(b2Contact * contact, const b2ContactImpulse * impulse) override;

	virtual void update(double step);
	virtual EntityType getType() const override;

private:
	static constexpr double FUSE_TIME = 3.0;
	static constexpr double RANGE = 10.0;

	Player & owner;
	double damage;
	bool canCollideWithOwner;

	double countdownToExplosion;
};

}}
