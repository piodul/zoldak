#include <SFML/Graphics.hpp>

#include <memory>

#include "../../ZkCommon/Constants.h"
#include "../../ZkCommon/LibraryCast.h"

#include "../Renderables/Renderable.h"
#include "../Renderables/CrosshairRenderable.h"

#include "Entity.h"
#include "CrosshairEntity.h"
#include "PlayerEntity.h"
#include "../GameSystem.h"
#include "../InputSystem.h"

using namespace Zk::Common;
using namespace Zk::Game;

CrosshairEntity::CrosshairEntity(
	std::weak_ptr<PlayerEntity> owner,
	MouseDeviceHandle mdh
)
	: Entity(nullptr, nullptr)
{
	this->owner = owner;
	this->mouseDevice = mdh;
	
	setRenderable(new CrosshairRenderable(owner));
}

CrosshairEntity::~CrosshairEntity()
{
	
}

void CrosshairEntity::update(double step)
{
	auto ptr = owner.lock();
	
	if (ptr != nullptr)
	{
		sf::Vector2f radius =
			GameSystem::getInstance()->getViewportDimensions();
		sf::Vector3i mouseDelta = mouseDevice.getRelativePosition();
		sf::Vector2f delta =
			sf::Vector2f((float)mouseDelta.x, (float)mouseDelta.y)
			* (float)Constants::METERS_PER_PIXEL;
		
		pos += delta;
		
		sf::Vector2f centerPos = ptr->getCenterPosition();
		
		//Może wyekstraktować to do jakiejś części odpowiedzialnej za majzę?
		if (pos.x > centerPos.x + radius.x)
			pos.x = centerPos.x + radius.x;
		if (pos.x < centerPos.x - radius.x)
			pos.x = centerPos.x - radius.x;
		
		if (pos.y > centerPos.y + radius.y)
			pos.y = centerPos.y + radius.y;
		if (pos.y < centerPos.y - radius.y)
			pos.y = centerPos.y - radius.y;
	}
	else
		markForDeletion();
}

sf::Vector2f CrosshairEntity::getCenterPosition() const
{
	return pos;
}

EntityType CrosshairEntity::getType() const
{
	return EntityType::CrosshairEntity;
}
