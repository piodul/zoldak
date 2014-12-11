#include <SFML/Graphics.hpp>

#include "../Player.hpp"

#include "MeshRenderable.hpp"
#include "Renderable.hpp"

using namespace Zk::Game;

MeshRenderable::MeshRenderable(
	const std::string & hierarchyPath,
	const sf::VertexArray & varr
)
	: Renderable(hierarchyPath)
{
	this->varr = varr;
}

MeshRenderable::~MeshRenderable()
{

}

void MeshRenderable::paint(sf::RenderTarget * rt, const Player & viewer)
{
	rt->draw(varr);
}
