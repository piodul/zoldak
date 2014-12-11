#include <SFML/Graphics.hpp>

#include <QtGui>
#include <QDebug>

#include <memory>

#include "../../ZkCommon/Constants.hpp"
#include "../../ZkCommon/LibraryCast.hpp"

#include "../Renderables/Renderable.hpp"
#include "../Renderables/CrosshairRenderable.hpp"

#include "Entity.hpp"
#include "CrosshairEntity.hpp"
#include "PlayerEntity.hpp"
#include "../GameSystem.hpp"
#include "../Game.hpp"
#include "../InputSystem.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

CrosshairEntity::CrosshairEntity(
	std::weak_ptr<PlayerEntity> owner,
	MouseDeviceHandle mdh
) :
	Entity(nullptr, nullptr),
	std::enable_shared_from_this<CrosshairEntity>()
{
	this->owner = owner;
	this->mouseDevice = mdh;
}

CrosshairEntity::~CrosshairEntity()
{

}

void CrosshairEntity::registerMe()
{
	setRenderable(new CrosshairRenderable(
		"UI",
		shared_from_this(), owner
	));
}

void CrosshairEntity::update(double step)
{
	auto ptr = owner.lock();

	if (ptr != nullptr)
	{
		sf::Vector2f radius =
			Game::getInstance()->getViewportDimensions();
		sf::Vector3i mouseDelta = mouseDevice.getRelativePosition();
		sf::Vector2f delta =
			sf::Vector2f((float)mouseDelta.x, (float)mouseDelta.y)
			* (float)Constants::METERS_PER_PIXEL;

		relativePos += delta;

		if (relativePos.x >  radius.x)
			relativePos.x =  radius.x;
		if (relativePos.x < -radius.x)
			relativePos.x = -radius.x;

		if (relativePos.y >  radius.y)
			relativePos.y =  radius.y;
		if (relativePos.y < -radius.y)
			relativePos.y = -radius.y;
	}
	else
		markForDeletion();
}

sf::Vector2f CrosshairEntity::getCenterPosition() const
{
	auto ptr = owner.lock();

	if (ptr != nullptr)
		return ptr->getCenterPosition() + relativePos;
	else
		return sf::Vector2f();
}

EntityType CrosshairEntity::getType() const
{
	return EntityType::CrosshairEntity;
}
