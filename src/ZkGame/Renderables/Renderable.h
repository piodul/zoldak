#pragma once

#include <SFML/Graphics.hpp>

namespace Zk {
namespace Game {

class Renderable
{
public:
	Renderable()
		: z(0.0)
	{  }
	virtual ~Renderable() {};
	
	virtual void paint(sf::RenderTarget * rt) = 0;
	
	inline double getZValue() const
	{ return z; }
	void setZValue(double z)
	{ this->z = z; }

private:
	double z;
};

}}
