#pragma once

#include "../Config/InputAction.h"

namespace Zk {
namespace Game {

class InputChoiceDialog
{
public:
	InputChoiceDialog() = delete;
	~InputChoiceDialog() = delete;
	
	static bool chooseInputAction(InputAction & ia);
};

}}
