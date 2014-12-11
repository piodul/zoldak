#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <memory>

#include "Entity.hpp"
#include "../InputSystem.hpp"

namespace Zk {
namespace Game {

class PlayerEntity;

class CrosshairEntity :
	public Entity,
	public std::enable_shared_from_this<CrosshairEntity>
{
public:
	CrosshairEntity(
		std::weak_ptr<PlayerEntity> owner,
		MouseDeviceHandle mdh
	);
	virtual ~CrosshairEntity();

	void registerMe();

	virtual void update(double step);

	virtual sf::Vector2f getCenterPosition() const;

	virtual EntityType getType() const;

protected:
	sf::Vector2f relativePos;
	std::weak_ptr<PlayerEntity> owner;
	MouseDeviceHandle mouseDevice;
};

}}
