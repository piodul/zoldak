#pragma once

#include <SFML/Graphics.hpp>

#include "SpawnerMeshEntity.h"
#include "Entity.h"

namespace Zk {
namespace Game {

class Renderable;

class MedKitEntity : public Entity
{
public:
	MedKitEntity(sf::Vector2f pos, SpawnerMeshEntity * spawner);
	virtual ~MedKitEntity();
	
	virtual void update(double step);
	virtual EntityType getType() const override;
	
	void pickUp();
	
private:
	SpawnerMeshEntity * spawner;
};

}}
