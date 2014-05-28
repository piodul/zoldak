#pragma once

#include <Box2D/Box2D.h>

namespace Zk {
namespace Game {

class PhysicsSystem;
class PhysicsComponent;
class PhysicsEvent;

class CollisionListener
{
public:
	virtual bool interestedInBeginContactEvent(b2Contact * contact) = 0;
	virtual bool interestedInEndContactEvent(b2Contact * contact) = 0;
	virtual void onBeginContactEvent(b2Contact * contact) = 0;
	virtual void onEndContactEvent(b2Contact * contact) = 0;
};

class BodyCollisionListener : public CollisionListener
{
public:
	BodyCollisionListener(b2Body * filteringBody);
	
	virtual bool interestedInBeginContactEvent(b2Contact * contact) override final;
	virtual bool interestedInEndContactEvent(b2Contact * contact) override final;
	
	inline b2Body * getFilteringBody() const
	{ return filteringBody; }
	
private:
	b2Body * filteringBody;
};

//Wrapper na Box2D i jego system eventów
class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();
	
	void registerListener(CollisionListener * pl);
	
private:
	b2World world;
	std::vector<CollisionListener*> collisionListeners;
};

}}
