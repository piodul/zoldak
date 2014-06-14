#include <QtCore>

#include "WeaponDef.h"

using namespace Zk::Game;

QDataStream & Zk::Game::operator<<(QDataStream & ds, const WeaponDef & wd)
{
	ds << wd.damagePerShot << wd.refireTime << (qint32)wd.clipSize << wd.reloadTime;
	return ds;
}

QDataStream & Zk::Game::operator>>(QDataStream & ds, WeaponDef & wd)
{
	qint32 cs;
	ds >> wd.damagePerShot >> wd.refireTime >> cs >> wd.reloadTime;
	wd.clipSize = cs;
	
	return ds;
}
