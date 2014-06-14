#pragma once

#include <QtCore>

namespace Zk {
namespace Game {

class WeaponDef
{
public:
	friend QDataStream & operator<<(QDataStream & ds, const WeaponDef & wd);
	friend QDataStream & operator>>(QDataStream & ds, WeaponDef & wd);
	
	///Ilość HP, ile odbiera pojedynczy strzał.
	double damagePerShot;
	
	///Czas w sekundach ile musi poczekać gracz, aby mógł wystrzelić ponownie.
	double refireTime;
	
	///Czas w sekundach potrzebny do całkowitego przeładowania broni.
	double reloadTime;
	
	///Rozmiar magazynku.
	int clipSize;
};

QDataStream & operator<<(QDataStream & ds, const WeaponDef & wd);
QDataStream & operator>>(QDataStream & ds, WeaponDef & wd);

}}
