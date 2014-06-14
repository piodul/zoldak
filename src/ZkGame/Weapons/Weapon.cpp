#include <QtCore>

#include <algorithm>

#include "WeaponDef.h"
#include "Weapon.h"

using namespace Zk::Game;

Weapon::Weapon(const WeaponDef & wd)
	: weaponDef(wd)
{
	shotCooldown = 0.0;
	reloadCooldown = 0.0;
	ammoLeftInClip = 0;
}

void Weapon::update(double step, bool triggered)
{
	if (ammoLeftInClip == 0)
	{
		//W trakcie przeładowywania
		reloadCooldown -= step;
		if (reloadCooldown <= 0.0)
		{
			reloadCooldown = 0.0;
			ammoLeftInClip = weaponDef.clipSize;
		}
	}
	else
	{
		if (shotCooldown > 0.0)
			shotCooldown = std::max(shotCooldown - step, 0.0);
		else
		{
			//Można strzelać
			if (triggered)
			{
				//Pew, pew!
				//---Tutaj będzie strzelanie---//
				ammoLeftInClip--;
				if (ammoLeftInClip == 0)
					reloadCooldown = weaponDef.reloadTime;
				else
					shotCooldown = weaponDef.refireTime;
			}
		}
	}
}
