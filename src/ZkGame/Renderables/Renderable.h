#pragma once

#include <SFML/Graphics.hpp>

namespace Zk {
namespace Game {

class Renderable
{
public:
	virtual ~Renderable() {};
	
	virtual void paint(sf::RenderTarget * rt) = 0;
};

}}
