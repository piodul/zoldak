#include <SFML/Graphics.hpp>

#include <algorithm>
#include <memory>

#include "../../Player.hpp"
#include "../Renderable.hpp"
#include "ContainerGraphicsLayer.hpp"

using namespace Zk::Game;

void ContainerGraphicsLayer::paint(sf::RenderTarget * rt, const Player & viewer)
{
	removeInactiveChildren();
	for (auto p : children)
	{
		auto r = p.lock();
		if (r->visibleToPlayer(viewer))
			r->paint(rt, viewer);
	}
}
