#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

namespace Zk {
namespace Game {

class Player;

class Renderable
{
public:
	Renderable()
		: z(0.0)
	{  }
	virtual ~Renderable() {};
	
	virtual void paint(sf::RenderTarget * rt) = 0;
	
	virtual bool visibleToPlayer(const Player & player)
	{ return true; }
	
	inline double getZValue() const
	{ return z; }
	void setZValue(double z)
	{ this->z = z; }

private:
	double z;
};

}}
