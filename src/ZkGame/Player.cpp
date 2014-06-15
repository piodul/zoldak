#include <algorithm>
#include <memory>

#include "Player.h"
#include "Entities/PlayerEntity.h"
#include "Config/InputConfig.h"
#include "SpawnerMesh.h"

using namespace Zk::Game;

Player::Player()
{
	timeToRespawn = 0.0;
}

void Player::setMouseDevice(MouseDeviceHandle md)
{
	mouseDevice = md;
}

void Player::setSpawnerMesh(const SpawnerMesh & sm)
{
	spawnerMesh = sm;
}

void Player::setInputConfig(const InputConfig & ic)
{
	inputConfig = ic;
}

void Player::setWeaponDef(const WeaponDef & wd)
{
	weaponDef = wd;
}

void Player::update(double step)
{
	timeToRespawn = std::max(0.0, timeToRespawn - step);
	if (timeToRespawn == 0.0)
	{
		auto ptr = entity.lock();
		if (ptr == nullptr)
		{
			ptr = std::make_shared<PlayerEntity>(
				spawnerMesh.pickSpawnLocation(),
				inputConfig,
				weaponDef
			);
			
			timeToRespawn = RESPAWN_TIME;
		}
	}
}
