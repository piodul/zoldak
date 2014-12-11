#include <QtCore>

#include "WeaponDef.hpp"

using namespace Zk::Game;

QDataStream & Zk::Game::operator<<(QDataStream & ds, const WeaponDef & wd)
{
	ds	<< wd.damagePerShot
		<< wd.muzzleVelocity
		<< wd.refireTime
		<< (qint32)wd.clipSize
		<< wd.reloadTime
		<< (qint32)wd.particleType;
	return ds;
}

QDataStream & Zk::Game::operator>>(QDataStream & ds, WeaponDef & wd)
{
	qint32 cs, pt;

	ds	>> wd.damagePerShot
		>> wd.muzzleVelocity
		>> wd.refireTime
		>> cs
		>> wd.reloadTime
		>> pt;

	wd.clipSize = cs;
	wd.particleType = (WeaponDef::ParticleType)wd.particleType;

	return ds;
}
