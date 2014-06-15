#pragma once

#include <QtCore>

namespace Zk {
namespace Game {

class WeaponDef
{
public:
	enum class ParticleType : int
	{
		BULLET = 0,
		GRENADE = 1
	};

	friend QDataStream & operator<<(QDataStream & ds, const WeaponDef & wd);
	friend QDataStream & operator>>(QDataStream & ds, WeaponDef & wd);

	///Ilość HP, które odbiera pojedynczy strzał.
	double damagePerShot;

	///Prędkość początkowa pocisku. (m/s)
	double muzzleVelocity;

	///Czas w sekundach, ile musi poczekać gracz, aby mógł wystrzelić ponownie.
	double refireTime;

	///Czas w sekundach potrzebny do całkowitego przeładowania broni.
	double reloadTime;

	///Rozmiar magazynku.
	int clipSize;

	///Typ pocisku.
	ParticleType particleType;
};

QDataStream & operator<<(QDataStream & ds, const WeaponDef & wd);
QDataStream & operator>>(QDataStream & ds, WeaponDef & wd);

}}
