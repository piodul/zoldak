#include <SFML/Graphics.hpp>

#include "MeshRenderable.h"
#include "Renderable.h"

using namespace Zk::Game;

MeshRenderable::MeshRenderable(const sf::VertexArray & varr)
{
	this->varr = varr;
}

MeshRenderable::~MeshRenderable()
{

}

void MeshRenderable::paint(sf::RenderTarget * rt)
{
	rt->draw(varr);
}
