#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace Zk {
namespace Game {

class Renderable;

class Entity
{
public:
	Entity(Renderable * vr, b2Body * pr);
	virtual ~Entity();
	
	virtual void update(double step) = 0;
	void paint(sf::RenderTarget * rt);
	
	virtual sf::Vector2f getCenterPosition() const;
	
	Renderable * getRenderable() const
	{ return visualRep; }
	inline b2Body * getBody() const
	{ return body; }
	
	inline bool wantsToBeDeleted() const
	{ return wannaDelete; }
	
protected:
	void setRenderable(Renderable * r);
	void setBody(b2Body * b);
	void markForDeletion();
	
private:
	Renderable * visualRep;
	b2Body * body;
	
	bool wannaDelete;
};

}}
