#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "InputSystem.h"
#include "SpawnerMesh.h"
#include "PlayerUI.h"
#include "Config/InputConfig.h"
#include "Weapons/WeaponDef.h"

namespace Zk {
namespace Game {

class PlayerEntity;
class TextureCache;

class Player
{
public:
	Player(int id, TextureCache & tc);
	
	///Ustawia uchwyt do myszki.
	void setMouseDevice(MouseDeviceHandle md);
	
	///Ustawia SpawnerMesh gracza.
	void setSpawnerMesh(const SpawnerMesh & sm);
	
	///Ustawia konfigurację klawiszy.
	void setInputConfig(const InputConfig & ic);
	
	///Ustawia definicję broni gracza.
	void setWeaponDef(const WeaponDef & wd);
	
	///Zwraca związany z graczem PlayerEntity
	std::weak_ptr<PlayerEntity> getPlayerEntity() const;
	
	///Zwraca id gracza.
	int getID() const;
	
	///Aktualizuje logikę respawnu gracza.
	void update(double step);
	
	///Rysuje interfejs dla gracza.
	void paintUI(sf::RenderTarget * rt);
	
private:
	static constexpr double RESPAWN_TIME = 5.0;
	
	std::weak_ptr<PlayerEntity> entity;
	SpawnerMesh spawnerMesh;
	MouseDeviceHandle mouseDevice;
	InputConfig inputConfig;
	WeaponDef weaponDef;
	PlayerUI ui;
	
	int id;
	double timeToRespawn;
};

}}
