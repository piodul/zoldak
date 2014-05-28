#pragma once

#include <SFML/Graphics.hpp>

namespace Zk {
namespace Game {

class Renderable
{
public:
	virtual ~Renderable() = 0;
	
	virtual void paint(sf::RenderTarget * rt) = 0;
};

}}
