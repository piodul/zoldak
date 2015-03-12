#pragma once

#include <QtCore>

#include <array>

#include "GraphicsConfig.hpp"
#include "InputConfig.hpp"
#include "SettingsConfig.hpp"

namespace Zk {
namespace Game {

class Config
{
public:
	Config() = default;

	friend QDataStream & operator<<(QDataStream & ds, const Config & c);
	friend QDataStream & operator>>(QDataStream & ds, Config & c);

	GraphicsConfig graphicsConfig;
	std::array<InputConfig, 2> playerInputConfig;
	SettingsConfig settingsConfig;
};

}}
