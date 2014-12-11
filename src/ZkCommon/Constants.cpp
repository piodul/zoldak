#include <string>
#include <map>

#include "Constants.hpp"

using namespace Zk::Common;

const std::string & Zk::Common::getLayerNameByType(LayerType lt)
{
	static std::map<LayerType, std::string> lt2s {
		{ LayerType::MEDKIT_SPAWN, "MEDKIT_SPAWN" },
		{ LayerType::GRENADES_SPAWN, "GRENADES_SPAWN" },
		{ LayerType::PLAYER_A_SPAWN, "PLAYER_A_SPAWN" },
		{ LayerType::PLAYER_B_SPAWN, "PLAYER_B_SPAWN" },
		{ LayerType::PLAYER_A_FLAG, "PLAYER_A_FLAG" },
		{ LayerType::PLAYER_B_FLAG, "PLAYER_B_FLAG" },
		{ LayerType::FOREGROUND, "FOREGROUND" },
		{ LayerType::MIDGROUND, "MIDGROUND" },
		{ LayerType::BACKGROUND, "BACKGROUND" },
		{ LayerType::MAX_LAYER, "MAX_LAYER" },
	};

	return lt2s[lt];
}
