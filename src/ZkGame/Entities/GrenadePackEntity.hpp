#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "CrateEntity.hpp"
#include "SpawnerMeshEntity.hpp"

namespace Zk {
namespace Game {

class Renderable;

class GrenadePackEntity : public CrateEntity
{
public:
	static constexpr double HP_PER_MEDKIT = 50.0;

	GrenadePackEntity(sf::Vector2f pos, SpawnerMeshEntity * spawner);
	virtual ~GrenadePackEntity();

	virtual void update(double step) override;
	virtual EntityType getType() const override;

	virtual void pickUp() override;

private:
	SpawnerMeshEntity * spawner;
};

}}
