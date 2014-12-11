#include <SFML/Graphics.hpp>

#include <QtCore>

#include <memory>

#include "../ZkCommon/Constants.hpp"

#include "PlayerUI.hpp"
#include "PlayerUILayout.hpp"
#include "Entities/PlayerEntity.hpp"
#include "Game.hpp"
#include "GameSystem.hpp"
#include "TextureCache.hpp"
#include "Camera.hpp"

#include "Weapons/Weapon.hpp"
#include "Weapons/WeaponDef.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

PlayerUI::PlayerUI(Player & player)
	: player(player)
{
	TextureCache & tc = GameSystem::getInstance()->getTextureCache();

	font.loadFromFile(
		GameSystem::resourcePath("SourceSansPro/SourceSansPro-Regular.otf")
	);
	healthTexture = tc.getTexture(GameSystem::resourcePath("life.png"));
	grenadeTexture = tc.getTexture(GameSystem::resourcePath("grenade.png"));
	ammoTexture = tc.getTexture(GameSystem::resourcePath("ammo.png"));
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::paint(sf::RenderTarget * rt)
{
	PlayerUILayout{rt, player, &font, healthTexture, grenadeTexture, ammoTexture}.paint();
}


