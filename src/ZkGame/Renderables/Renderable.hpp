#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

#include "../Player.hpp"

namespace Zk {
namespace Game {

class Player;

class Renderable
{
public:
	Renderable(const std::string & hierarchyPath)
		: hierarchyPath(hierarchyPath)
	{  }
	virtual ~Renderable() {};

	virtual void paint(sf::RenderTarget * rt, const Player & viewer) = 0;

	virtual bool visibleToPlayer(const Player & player)
	{ return true; }

	virtual bool isGraphicsLayer() const
	{ return false; }

	const std::string & getHierarchyPath() const
	{ return hierarchyPath; }

private:
	std::string hierarchyPath;
};

}}
