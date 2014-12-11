#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <string>

#include "../Player.hpp"
#include "Renderable.hpp"

namespace Zk {
namespace Game {

class BoxRenderable : public Renderable
{
public:
	BoxRenderable(
		const std::string & hierarchyPath,
		const b2Body * body,
		const char * imgSrc
	);
	virtual ~BoxRenderable();

	virtual void paint(sf::RenderTarget * rt, const Player & viewer);

private:
	sf::Texture * texture;
	sf::Sprite sprite;

	const b2Body * body;
};

}}
