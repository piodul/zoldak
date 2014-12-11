#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../Renderable.hpp"

namespace Zk {
namespace Game {

class GraphicsLayer : public Renderable
{
public:
	GraphicsLayer(
		const std::string & hierarchyPath,
		const std::string & name
	)
		: Renderable(hierarchyPath)
		, name(name)
	{}
	virtual ~GraphicsLayer() {}

	virtual bool isGraphicsLayer() const
	{ return true; }

	const std::string & getName() const
	{ return name; }

	bool addChild(std::weak_ptr<Renderable> r);

protected:
	std::vector<std::weak_ptr<Renderable>> children;

	void removeInactiveChildren();

private:
	std::string name;

	bool addChildInner(std::string path, std::weak_ptr<Renderable> r);
	virtual bool onRegisterChild(std::weak_ptr<Renderable> r)
	{ return true; }
};

}}
