#pragma once

#include <SFML/Graphics.hpp>

#include "CrateEntity.hpp"

namespace Zk {
	namespace Game {

		class SpawnerMeshEntity;
		class Renderable;

		class QuadDamageEntity : public CrateEntity
		{
		public:
			static const int QuadTime;

			QuadDamageEntity(sf::Vector2f pos, SpawnerMeshEntity * spawner);
			virtual ~QuadDamageEntity();

			virtual void update(double step) override;
			virtual EntityType getType() const override;

			virtual void pickUp() override;

		private:
			SpawnerMeshEntity * spawner;
		};

	}}
