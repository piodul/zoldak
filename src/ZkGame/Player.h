#pragma once

#include <memory>

#include "InputSystem.h"
#include "SpawnerMesh.h"
#include "Config/InputConfig.h"
#include "Weapons/WeaponDef.h"

namespace Zk {
namespace Game {

class PlayerEntity;

class Player
{
public:
	Player();
	
	///Ustawia uchwyt do myszki.
	void setMouseDevice(MouseDeviceHandle md);
	
	///Ustawia SpawnerMesh gracza.
	void setSpawnerMesh(const SpawnerMesh & sm);
	
	///Ustawia konfigurację klawiszy.
	void setInputConfig(const InputConfig & ic);
	
	///Ustawia definicję broni gracza.
	void setWeaponDef(const WeaponDef & wd);
	
	///Aktualizuje logikę respawnu gracza.
	void update(double step);
	
private:
	static constexpr double RESPAWN_TIME = 5.0;
	
	std::weak_ptr<PlayerEntity> entity;
	SpawnerMesh spawnerMesh;
	MouseDeviceHandle mouseDevice;
	InputConfig inputConfig;
	WeaponDef weaponDef;
	
	double timeToRespawn;
};

}}
