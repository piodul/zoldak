#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

#include "Entity.h"
#include "../InputSystem.h"

namespace Zk {
namespace Game {

class MouseTrackEntity : public Entity
{
public:
	MouseTrackEntity(const MouseDeviceHandle & mdh);
	virtual ~MouseTrackEntity();
	
	virtual void update(double step) override;
	virtual EntityType getType() const override;
	
	virtual sf::Vector2f getCenterPosition() const override;
	
private:
	sf::Vector2f currPos;
	MouseDeviceHandle mdh;
};

}}
