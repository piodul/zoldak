#pragma once

#include <QtCore>

namespace Zk {
namespace Game {

class WeaponDef
{
public:
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
};

QDataStream & operator<<(QDataStream & ds, const WeaponDef & wd);
QDataStream & operator>>(QDataStream & ds, WeaponDef & wd);

}}
