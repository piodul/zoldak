#include <QtCore>

#include <map>

#include "Config.hpp"

using namespace Zk::Game;

Config::Config()
{

}

QDataStream & Zk::Game::operator<<(QDataStream & ds, const Config & c)
{
	ds << c.graphicsConfig;
	ds << c.playerInputConfig[0];
	ds << c.playerInputConfig[1];
	ds << c.settingsConfig;

	return ds;
}

QDataStream & Zk::Game::operator>>(QDataStream & ds, Config & c)
{
	ds >> c.graphicsConfig;
	ds >> c.playerInputConfig[0];
	ds >> c.playerInputConfig[1];
	ds >> c.settingsConfig;

	return ds;
}
