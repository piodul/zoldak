#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "InputSystem.hpp"
#include "SpawnerMesh.hpp"
#include "PlayerUI.hpp"
#include "Config/InputConfig.hpp"
#include "Weapons/WeaponDef.hpp"

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
	std::weak_ptr<PlayerEntity> entity;
	SpawnerMesh spawnerMesh;
	InputConfig inputConfig;
	PlayerUI ui;

	int id;
	int numKills, numDeaths;
	double timeToRespawn;
};

}}
