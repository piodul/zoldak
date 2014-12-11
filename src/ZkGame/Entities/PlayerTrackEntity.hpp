#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "Entity.hpp"
#include "../InputSystem.hpp"

namespace Zk {
namespace Game {

class PlayerTrackEntity : public Entity
{
public:
	PlayerTrackEntity(int trackedPlayer);
	virtual ~PlayerTrackEntity();

	virtual void update(double step) override;
	virtual EntityType getType() const override;

	virtual sf::Vector2f getCenterPosition() const override;

private:
	int trackedPlayer;
	sf::Vector2f currPos;
};

}}
