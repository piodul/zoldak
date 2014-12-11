#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "WeaponDef.hpp"

namespace Zk {
namespace Game {

class Player;

class Weapon
{
public:
	///Konstruuje nową broń na podstawie definicji.
	Weapon(const WeaponDef & wd, Player & owner);

	///Aktualizuje liczniki chłodzenia/przeładowywania,
	///oraz wystrzeliwuje pocisk, gdy triggered oraz
	///broń jest gotowa do wystrzału.
	void update(double step, sf::Vector2f direction, bool triggered);

	///Natychmiast dodaje naboje do magazynka.
	void loadAmmo(int count);

	///Zwraca wartość z przedziału [0, 1] oznaczającą
	///postęp przeładowywania. 0 - początek
	///przeładowywania, 1 - niepusty magazynek.
	double reloadProgress() const;

	///Zwraca wartośc z przedziału [0, 1] oznaczającą
	///postęp w chłodzeniu broni. 0 - chwilę po
	///wystrzale, 1 - można strzelać.
	double refireProgress() const;

	///Zwraca ilość amunicji w magazynku.
	int getAmmoCount() const;

	///Zwraca definicję, na podstawie której ta broń została stworzona.
	const WeaponDef & getWeaponDef() const;

private:
	///Ilość sekund do całkowitego ochłodzenia.
	double shotCooldown;

	///Ilość sekund do przeładowania.
	double reloadCooldown;

	///Ilość amunicji w magazynku.
	int ammoLeftInClip;

	///Właściciel broni.
	Player & owner;

	///Definicja, na której bazuje ta broń.
	WeaponDef weaponDef;
};

}}
