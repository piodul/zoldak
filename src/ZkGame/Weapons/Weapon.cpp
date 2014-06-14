#include <QtCore>

#include <algorithm>
#include <memory>

#include "WeaponDef.h"
#include "Weapon.h"
#include "../Entities/BulletEntity.h"
#include "../Entities/PlayerEntity.h"

#include "../GameSystem.h"

using namespace Zk::Game;

Weapon::Weapon(const WeaponDef & wd)
	: weaponDef(wd)
{
	shotCooldown = 0.0;
	reloadCooldown = 0.0;
	ammoLeftInClip = 0;
	this->owner = owner;
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
				
				auto ptr = owner.lock();
				
				if (ptr != nullptr)
				{
					auto be = std::make_shared<BulletEntity>(
						ptr->getCenterPosition(),
						sf::Vector2f(25.f, 0.f),
						owner,
						weaponDef.damagePerShot
					);
					
					be->registerMe();
					
					GameSystem::getInstance()->addEntity(be);
					
					ammoLeftInClip--;
					if (ammoLeftInClip == 0)
						reloadCooldown = weaponDef.reloadTime;
					else
						shotCooldown = weaponDef.refireTime;
				}
			}
		}
	}
}

double Weapon::reloadProgress() const
{
	return 1.0 - (reloadCooldown / weaponDef.reloadTime);
}

double Weapon::refireProgress() const
{
	return 1.0 - (shotCooldown / weaponDef.refireTime);
}

void Weapon::setOwner(std::shared_ptr<PlayerEntity> owner)
{
	this->owner = owner;
}
