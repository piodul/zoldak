#include <SFML/Graphics.hpp>

#include "../../ZkCommon/Constants.h"

#include "MouseTrackEntity.h"
#include "../InputSystem.h"

using namespace Zk::Common;
using namespace Zk::Game;

static const float CONVERGE_TEMPO = 0.2f;

MouseTrackEntity::MouseTrackEntity(const MouseDeviceHandle & mdh)
	: Entity(nullptr, nullptr), mdh(mdh)
{
	
}

MouseTrackEntity::~MouseTrackEntity()
{
	
}

void MouseTrackEntity::update(double step)
{
	sf::Vector3i v = -mdh.getAbsolutePosition();
	sf::Vector2f target =
		sf::Vector2f((float)v.x, (float)v.y) * (float)Constants::METERS_PER_PIXEL;
	currPos = (1.f - CONVERGE_TEMPO) * currPos + CONVERGE_TEMPO * target;
}

EntityType MouseTrackEntity::getType() const
{
	return EntityType::MouseTrackEntity;
}

sf::Vector2f MouseTrackEntity::getCenterPosition() const
{
	return currPos;
}
