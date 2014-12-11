#pragma once

#include <SFML/Graphics.hpp>

#include "Renderable.hpp"

namespace Zk {
namespace Game {

class MeshRenderable : public Renderable
{
public:
	MeshRenderable(
		const std::string & hierarchyPath,
		const sf::VertexArray & varr
	);
	virtual ~MeshRenderable();

	virtual void paint(sf::RenderTarget * rt, const Player & viewer);

private:
	sf::VertexArray varr;
};

}}
