#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Renderable.h"

namespace Zk {
namespace Game {

class BoxRenderable : public Renderable
{
public:
	BoxRenderable(
		const b2Body * body,
		const char * imgSrc
	);
	virtual ~BoxRenderable();
	
	virtual void paint(sf::RenderTarget * rt);
	
private:
	sf::Texture texture;
	sf::Sprite sprite;
	
	const b2Body * body;
};

}}
