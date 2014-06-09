#pragma once

#include <QtCore>

#include <array>

#include "InputConfig.h"

namespace Zk {
namespace Game {

class Config
{
public:
	Config();
	
	friend QDataStream & operator<<(QDataStream & ds, const Config & c);
	friend QDataStream & operator>>(QDataStream & ds, Config & c);
	
	std::array<InputConfig, 2> playerInputConfig;
};

}}
