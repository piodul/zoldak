#pragma once

#include <QtCore>

#include <array>
#include <map>

#include "PlayerAction.h"
#include "InputAction.h"
#include "../InputSystem.h"

namespace Zk {
namespace Game {

class InputConfig
{
public:
	InputConfig();

	friend QDataStream & operator<<(QDataStream & ds, const InputConfig & ic);
	friend QDataStream & operator>>(QDataStream & ds, InputConfig & ic);

	std::map<PlayerAction, InputAction> playerToInput;
	MouseDeviceHandle mouseDevice;

	bool isActionTriggered(PlayerAction pa) const;
};

}}
