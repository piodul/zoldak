#pragma once

#include <QtCore>

#include <map>

namespace Zk {
namespace Game {

enum class PlayerAction : int
{
	GoLeft = 0,
	GoRight,
	Jump,
	ThrowGrenade,
	Shoot,

	NUM_ACTIONS
};

const char * playerActionToName(PlayerAction pa);

}}
