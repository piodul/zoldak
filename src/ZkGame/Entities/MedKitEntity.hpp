#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "CrateEntity.hpp"
#include "SpawnerMeshEntity.hpp"

namespace Zk {
namespace Game {

class Renderable;

class MedKitEntity : public CrateEntity
{
public:
	static constexpr double HP_PER_MEDKIT = 50.0;

	MedKitEntity(sf::Vector2f pos, SpawnerMeshEntity * spawner);
	virtual ~MedKitEntity();

	virtual void update(double step) override;
	virtual EntityType getType() const override;

	virtual void pickUp() override;

private:
	SpawnerMeshEntity * spawner;
};

}}
