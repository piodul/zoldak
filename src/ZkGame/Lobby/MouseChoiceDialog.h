#pragma once

#include "../InputSystem.h"

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
