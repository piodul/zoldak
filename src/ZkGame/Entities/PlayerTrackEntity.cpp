#include <SFML/Graphics.hpp>

#include <array>

#include "../../ZkCommon/Constants.hpp"

#include "Entity.hpp"
#include "PlayerTrackEntity.hpp"
#include "PlayerEntity.hpp"
#include "CrosshairEntity.hpp"
#include "../GameSystem.hpp"
#include "../Game.hpp"
#include "../InputSystem.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

static const float CONVERGE_TEMPO = 0.2f;

PlayerTrackEntity::PlayerTrackEntity(int trackedPlayer)
	: Entity(nullptr, nullptr)
{
	this->trackedPlayer = trackedPlayer;
}

PlayerTrackEntity::~PlayerTrackEntity()
{

}

void PlayerTrackEntity::update(double step)
{
	sf::Vector2f target(0.f, 0.f);
	auto players = Game::getInstance()->getPlayers();
	int p = trackedPlayer;

	if (players[p].getPlayerEntity().lock() == nullptr)
		p = 1 - p;

	if (players[p].getPlayerEntity().lock() != nullptr)
	{
		auto ptr = players[p].getPlayerEntity().lock();
		target = (
			ptr->getCenterPosition() +
			ptr->getCrosshairEntity().lock()->getCenterPosition()
		) * 0.5f;
	}

	currPos = (1.f - CONVERGE_TEMPO) * currPos + CONVERGE_TEMPO * target;
}

EntityType PlayerTrackEntity::getType() const
{
	return EntityType::PlayerTrackEntity;
}

sf::Vector2f PlayerTrackEntity::getCenterPosition() const
{
	return currPos;
}
