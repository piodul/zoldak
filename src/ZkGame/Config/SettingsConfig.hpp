#pragma once

#include <QtCore>

namespace Zk {
namespace Game {

class SettingsConfig : public QObject
{
	Q_OBJECT;

public:
	SettingsConfig(QObject * parent = nullptr);

	double respawnTime() const;
	int maxGrenadePacksOnMap() const;
	int maxMedkitsOnMap() const;
	bool enabledFovEffect() const;

public slots:
	void setRespawnTime(double respawnTime);
	void setMaxGrenadePacksOnMap(int maxGrenadePacksOnMap);
	void setMaxMedkitsOnMap(int maxMedkitsOnMap);
	void setEnabledFovEffect(bool enabledFovEffect);

	friend QDataStream & operator<<(QDataStream & ds, const SettingsConfig & gc);
	friend QDataStream & operator>>(QDataStream & ds, SettingsConfig & gc);

private:
	double respawnTime_;
	int maxGrenadePacksOnMap_;
	int maxMedkitsOnMap_;
	bool enabledFovEffect_;
};

QDataStream & operator<<(QDataStream & ds, const SettingsConfig & gc);
QDataStream & operator>>(QDataStream & ds, SettingsConfig & gc);

}}
