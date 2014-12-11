#pragma once

#include <QtCore>

#include <array>
#include <map>

#include "PlayerAction.hpp"
#include "InputAction.hpp"
#include "../InputSystem.hpp"

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
