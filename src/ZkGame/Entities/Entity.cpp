#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "../../ZkCommon/LibraryCast.h"

#include "Entity.h"
#include "../Renderables/Renderable.h"

using namespace Zk::Common;
using namespace Zk::Game;

Entity::Entity(Renderable * vr, b2Body * pr)
{
	visualRep = vr;
	body = pr;
}

Entity::~Entity()
{
	delete visualRep;
	
	if (body)
	{
		b2World * world = body->GetWorld();
		world->DestroyBody(body);
	}
}

void Entity::paint(sf::RenderTarget * rt)
{
	if (visualRep)
		visualRep->paint(rt);
}

sf::Vector2f Entity::getCenterPosition() const
{
	if (getBody() != nullptr)
		return lib_cast<sf::Vector2f>(getBody()->GetPosition());
	else
		return sf::Vector2f(0.f, 0.f);
}

void Entity::setRenderable(Renderable * r)
{
	delete visualRep;
	visualRep = r;
}

void Entity::setBody(b2Body * b)
{
	if (body)
	{
		b2World * world = body->GetWorld();
		world->DestroyBody(body);
	}
	
	body = b;
}

void Entity::markForDeletion()
{
	wannaDelete = true;
}
