#include <map>

#include "PlayerAction.hpp"

using namespace Zk::Game;

const char * Zk::Game::playerActionToName(PlayerAction pa)
{
	static const std::map<PlayerAction, const char*> playerActionName {
		{ PlayerAction::GoLeft,			"Walk left" },
		{ PlayerAction::GoRight,		"Walk right" },
		{ PlayerAction::Jump,			"Jump" },
		{ PlayerAction::ThrowGrenade,	"Throw grenade" },
		{ PlayerAction::Shoot,			"Shoot" }
	};

	auto it = playerActionName.find(pa);

	return (it != playerActionName.end()) ? it->second : "???";
}
