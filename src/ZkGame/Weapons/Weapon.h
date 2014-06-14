#pragma once

#include "WeaponDef.h"

namespace Zk {
namespace Game {

class Weapon
{
public:
	///Konstruuje nową broń na podstawie definicji.
	Weapon(const WeaponDef & wd);
	
	///Aktualizuje liczniki chłodzenia/przeładowywania,
	///oraz wystrzeliwuje pocisk, gdy triggered oraz
	///broń jest gotowa do wystrzału.
	void update(double step, bool triggered);
	
	///Zwraca wartość z przedziału [0, 1] oznaczającą
	///postęp przeładowywania. 0 - początek
	///przeładowywania, 1 - niepusty magazynek.
	double reloadProgress() const;
	
	///Zwraca wartośc z przedziału [0, 1] oznaczającą
	///postęp w chłodzeniu broni. 0 - chwilę po
	///wystrzale, 1 - można strzelać.
	double refireProgress() const;
	
private:
	///Ilość sekund do całkowitego ochłodzenia.
	double shotCooldown;
	
	///Ilość sekund do przeładowania.
	double reloadCooldown;
	
	///Ilość amunicji w magazynku.
	int ammoLeftInClip;
	
	///Definicja, na której bazuje ta broń.
	WeaponDef weaponDef;
};

}}
