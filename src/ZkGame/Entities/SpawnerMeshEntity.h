#pragma once

#include <SFML/Graphics.hpp>

#include "../../ZkCommon/Constants.h"
#include "Entity.h"

namespace Zk {
	
namespace Common { class LevelLayer; }
namespace Game {

class Renderable;

class SpawnerMeshEntity : public Entity
{
public:
	SpawnerMeshEntity(const Common::LevelLayer * ll, Common::LayerType lt);
	virtual ~SpawnerMeshEntity();
	
	virtual void update(double step);
	virtual EntityType getType() const override;
	
	void entityPickedUp();
	
private:
	void spawnEntity();
	
	static constexpr double COOLDOWN_IN_SECONDS = 5.0;
	
	const Common::LevelLayer * ll;
	sf::VertexArray varr;
	Common::LayerType lt;
	
	double cooldown;
	int itemCount, maxItemCount;
};

}}
