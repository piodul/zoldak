#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

namespace Zk {
	
namespace Common { class LevelLayer; }
namespace Game {

class Renderable;

class SpawnerMeshEntity : public Entity
{
public:
	SpawnerMeshEntity(const Common::LevelLayer * ll);
	virtual ~SpawnerMeshEntity();
	
	virtual void update(double step);
	virtual EntityType getType() const override;
	
private:
	const Common::LevelLayer * ll;
};

}}
