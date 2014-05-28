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
	
	Renderable * getRenderable() const;
	b2Body * getBody() const;
	
private:
	Renderable * visualRep;
	b2Body * physicalRep;
};

}}
