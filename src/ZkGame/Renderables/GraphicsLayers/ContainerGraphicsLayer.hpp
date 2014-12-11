#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <memory>

#include "../../Player.hpp"
#include "../Renderable.hpp"
#include "GraphicsLayer.hpp"

namespace Zk {
namespace Game {

class ContainerGraphicsLayer : public GraphicsLayer
{
public:
	ContainerGraphicsLayer(
		const std::string & hierarchyPath,
		const std::string & name
	)
		: GraphicsLayer(hierarchyPath, name)
	{}
	virtual ~ContainerGraphicsLayer() {}

	virtual void paint(sf::RenderTarget * rt, const Player & viewer);
};

}}
