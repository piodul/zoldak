#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

namespace Zk {
	
namespace Common { class LevelLayer; }
namespace Game {

class Renderable;

class LevelMeshEntity : public Entity
{
public:
	LevelMeshEntity(const Common::LevelLayer * ll);
	virtual ~LevelMeshEntity();
	
	virtual void update(double step);
	virtual EntityType getType() const override;
	
private:
	const Common::LevelLayer * ll;
};

}}
