#include <SFML/Graphics.hpp>

#include <QtCore>

#include <algorithm>
#include <memory>

#include "WeaponDef.hpp"
#include "Weapon.hpp"
#include "../Entities/BulletEntity.hpp"
#include "../Entities/GrenadeEntity.hpp"
#include "../Entities/PlayerEntity.hpp"

#include "../Player.hpp"
#include "../Game.hpp"

using namespace Zk::Game;

Weapon::Weapon(const WeaponDef & wd, Player & owner)
	: owner(owner), weaponDef(wd)
{
	shotCooldown = 0.0;
	reloadCooldown = 0.0;
	ammoLeftInClip = 0;
}

void Weapon::update(double step, sf::Vector2f direction, bool triggered)
{
	if (ammoLeftInClip == 0)
	{
		//W trakcie przeładowywania
		if (weaponDef.particleType == WeaponDef::ParticleType::BULLET)
		{
			reloadCooldown -= step;
			if (reloadCooldown <= 0.0)
			{
				reloadCooldown = 0.0;
				ammoLeftInClip = weaponDef.clipSize;
			}
		}
	}
	else
	{
		if (shotCooldown > 0.0)
			shotCooldown = std::max(shotCooldown - step, 0.0);
		else
		{
			//Można strzelać
			if (triggered && direction != sf::Vector2f(0.f, 0.f))
			{
				//Pew, pew!

				auto ptr = owner.getPlayerEntity().lock();

				if (ptr != nullptr)
				{
					float scalingFactor =
						weaponDef.muzzleVelocity /
						sqrtf(direction.x * direction.x + direction.y * direction.y);

					switch (weaponDef.particleType)
					{
					case WeaponDef::ParticleType::BULLET:
						{
							auto be = std::make_shared<BulletEntity>(
								ptr->getCenterPosition(),
								direction * scalingFactor,
								owner,
								weaponDef.damagePerShot
							);

							be->registerMe();

							Game::getInstance()->addEntity(be);
						}
						break;
					case WeaponDef::ParticleType::GRENADE:
						{
							auto be = std::make_shared<GrenadeEntity>(
								ptr->getCenterPosition(),
								direction * scalingFactor,
								owner,
								weaponDef.damagePerShot
							);

							be->registerMe();

							Game::getInstance()->addEntity(be);
						}
						break;
					}

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

void Weapon::loadAmmo(int count)
{
	if (count > 0)
		ammoLeftInClip = std::min(ammoLeftInClip + count, weaponDef.clipSize);
}

double Weapon::reloadProgress() const
{
	return 1.0 - (reloadCooldown / weaponDef.reloadTime);
}

double Weapon::refireProgress() const
{
	return 1.0 - (shotCooldown / weaponDef.refireTime);
}

int Weapon::getAmmoCount() const
{
	return ammoLeftInClip;
}

const WeaponDef & Weapon::getWeaponDef() const
{
	return weaponDef;
}
