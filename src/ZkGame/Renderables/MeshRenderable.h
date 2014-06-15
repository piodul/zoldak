#pragma once

#include <SFML/Graphics.hpp>

#include "Renderable.h"

namespace Zk {
namespace Game {

class MeshRenderable : public Renderable
{
public:
	MeshRenderable(const sf::VertexArray & varr);
	virtual ~MeshRenderable();

	virtual void paint(sf::RenderTarget * rt);

private:
	sf::VertexArray varr;
};

}}
