#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Entity.h"
#include "Renderable.h"

using namespace Zk::Game;

Entity::Entity(Renderable * vr, b2Body * pr)
{
	visualRep = vr;
	physicalRep = pr;
}

Entity::~Entity()
{
	delete visualRep;
	
	if (physicalRep)
	{
		b2World * world = physicalRep->GetWorld();
		world->DestroyBody(physicalRep);
	}
}

void Entity::paint(sf::RenderTarget * rt)
{
	if (visualRep)
		visualRep->paint(rt);
}
