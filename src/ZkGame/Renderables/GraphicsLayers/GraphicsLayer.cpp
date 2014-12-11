#include <algorithm>
#include <memory>

#include "../../Player.hpp"

#include "../Renderable.hpp"
#include "GraphicsLayer.hpp"

using namespace Zk::Game;

bool GraphicsLayer::addChild(std::weak_ptr<Renderable> r)
{
	if (r.expired())
		return false;

	auto pPtr = r.lock();
	return addChildInner(pPtr->getHierarchyPath(), r);
}

bool GraphicsLayer::addChildInner(std::string path, std::weak_ptr<Renderable> r)
{
	size_t s = path.find_first_not_of('/');
	path.erase(0, s);

	if (path.empty())
	{
		bool doInclude = onRegisterChild(r);
		if (doInclude)
			children.emplace_back(r);

		return doInclude;
	}

	size_t slashPos = std::min(path.find_first_of('/'), path.length());
	std::string nextToken = path.substr(0, slashPos);

	for (auto p : children)
	{
		auto pPtr = p.lock();
		if (pPtr == nullptr)
			continue;

		if (pPtr->isGraphicsLayer())
		{
			auto gl = std::static_pointer_cast<GraphicsLayer>(pPtr);
			if (gl->getName() == nextToken)
				return gl->addChildInner(
					path.substr(slashPos, std::string::npos),
					r
				);
		}
	}

	return false;
}

void GraphicsLayer::removeInactiveChildren()
{
	auto end = std::remove_if(
		children.begin(), children.end(),
		[](const std::weak_ptr<Renderable> & ptr) -> bool
		{
			return ptr.expired();
		}
	);

	children.erase(end, children.end());
}
