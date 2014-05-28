#include <Box2D/Box2D.h>

#include "Physics.h"

using namespace Zk::Game;

BodyCollisionListener::BodyCollisionListener(b2Body * filteringBody)
{
	this->filteringBody = filteringBody;
}

static bool contactContainsBody(b2Contact * contact, b2Body * body)
{
	return (body == contact->GetFixtureA()->GetBody())
		|| (body == contact->GetFixtureB()->GetBody());
}

bool BodyCollisionListener::interestedInBeginContactEvent(b2Contact * contact)
{
	return contactContainsBody(contact, filteringBody);
}

bool BodyCollisionListener::interestedInEndContactEvent(b2Contact * contact)
{
	return contactContainsBody(contact, filteringBody);
}

PhysicsSystem::PhysicsSystem()
	: world(b2Vec2(0.0, 0.0))
{
	
}

PhysicsSystem::~PhysicsSystem()
{
	
}
