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
	Player(int id);
	
	///Ustawia SpawnerMesh gracza.
	void setSpawnerMesh(const SpawnerMesh & sm);
	
	///Ustawia konfigurację klawiszy.
	void setInputConfig(const InputConfig & ic);
	
	///Ustawia definicję broni gracza.
	void setWeaponDef(const WeaponDef & wd);
	
	///Raportuje dokonanie zabójstwa przez gracza.
	void reportKill();
	
	///Raportuje śmierć gracza.
	void reportDeath();
	
	///Zwraca związany z graczem PlayerEntity.
	std::weak_ptr<PlayerEntity> getPlayerEntity() const;
	
	///Zwraca id gracza.
	int getID() const;
	
	///Zwraca ilość zabójstw dokonanych przez gracza.
	int getKillCount() const;
	
	///Zwraca ilość śmierci gracza.
	int getDeathCount() const;
	
	///Zwraca ilość do respawnu, gdy gracz nie żyje.
	double getSecondsToRespawn() const;
	
	///Aktualizuje logikę respawnu gracza.
	void update(double step);
	
	///Rysuje interfejs dla gracza.
	void paintUI(sf::RenderTarget * rt);
	
private:
	static constexpr double RESPAWN_TIME = 5.0;
	
	std::weak_ptr<PlayerEntity> entity;
	SpawnerMesh spawnerMesh;
	InputConfig inputConfig;
	WeaponDef weaponDef;
	PlayerUI ui;
	
	int id;
	int numKills, numDeaths;
	double timeToRespawn;
};

}}
