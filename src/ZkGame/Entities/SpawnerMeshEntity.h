#pragma once

#include <SFML/Graphics.hpp>

#include "../SpawnerMesh.h"

#include "../../ZkCommon/Constants.h"
#include "Entity.h"

namespace Zk {
	
namespace Common { class LevelLayer; }
namespace Game {

class Renderable;

///Automatyczny spawner skrzynek z granatami lub medkitów.
class SpawnerMeshEntity : public Entity
{
public:
	SpawnerMeshEntity(const Common::LevelLayer * ll, Common::LayerType lt);
	virtual ~SpawnerMeshEntity();
	
	virtual void update(double step);
	virtual EntityType getType() const override;
	
	void entityPickedUp();
	
private:
	static constexpr double COOLDOWN_IN_SECONDS = 5.0;
	
	SpawnerMesh spawnerMesh;
	Common::LayerType lt;
	
	double cooldown;
	int itemCount, maxItemCount;
};

}}
