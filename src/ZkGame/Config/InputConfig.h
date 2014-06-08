#pragma once

#include <array>
#include <map>

#include "PlayerAction.h"
#include "InputAction.h"

namespace Zk {
namespace Game {

class InputConfig
{
public:
	InputConfig();
	~InputConfig();
	
	std::array<std::map<InputAction, PlayerAction>, 2> ;
};

}}
