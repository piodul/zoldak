#pragma once

#include "../InputSystem.hpp"

namespace Zk {
namespace Game {

class MouseChoiceDialog
{
public:
	MouseChoiceDialog() = delete;
	~MouseChoiceDialog() = delete;

	static bool chooseMouse(MouseDeviceHandle & mdh);
};

}}
