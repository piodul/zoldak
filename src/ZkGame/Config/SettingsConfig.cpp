#include <QtCore>

#include "../../ZkCommon/Constants.hpp"

#include "SettingsConfig.hpp"

using namespace Zk::Game;
using namespace Zk::Common::Constants::Defaults;

SettingsConfig::SettingsConfig(QObject * parent)
	: QObject(parent)
	, respawnTime_(RESPAWN_TIME)
	, maxGrenadePacksOnMap_(MAX_GRENADE_PACKS_ON_MAP)
	, maxMedkitsOnMap_(MAX_MEDKITS_ON_MAP)
	, enabledFovEffect_(false)
{}

double SettingsConfig::respawnTime() const
{
	return respawnTime_;
}

int SettingsConfig::maxGrenadePacksOnMap() const
{
	return maxGrenadePacksOnMap_;
}

int SettingsConfig::maxMedkitsOnMap() const
{
	return maxMedkitsOnMap_;
}

bool SettingsConfig::enabledFovEffect() const
{
	return enabledFovEffect_;
}

void SettingsConfig::setRespawnTime(double respawnTime)
{
	respawnTime_ = respawnTime;
}

void SettingsConfig::setMaxGrenadePacksOnMap(int maxGrenadePacksOnMap)
{
	maxGrenadePacksOnMap_ = maxGrenadePacksOnMap;
}

void SettingsConfig::setMaxMedkitsOnMap(int maxMedkitsOnMap)
{
	maxMedkitsOnMap_ = maxMedkitsOnMap;
}

void SettingsConfig::setEnabledFovEffect(bool enabledFovEffect)
{
	enabledFovEffect_ = enabledFovEffect;
}

QDataStream & Zk::Game::operator<<(QDataStream & ds, const SettingsConfig & sc)
{
	ds	<< sc.respawnTime()
		<< sc.maxGrenadePacksOnMap()
		<< sc.maxMedkitsOnMap()
		<< sc.enabledFovEffect();

	return ds;
}

QDataStream & Zk::Game::operator>>(QDataStream & ds, SettingsConfig & sc)
{
	double respawnTime;
	int maxGrenades, maxMedkits;
	bool enabledFovEffect;
	ds >> respawnTime >> maxGrenades >> maxMedkits >> enabledFovEffect;

	sc.setRespawnTime(respawnTime);
	sc.setMaxGrenadePacksOnMap(maxGrenades);
	sc.setMaxMedkitsOnMap(maxMedkits);
	sc.setEnabledFovEffect(enabledFovEffect);

	return ds;
}
