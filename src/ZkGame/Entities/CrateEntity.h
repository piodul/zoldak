#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

namespace Zk {
namespace Game {

class Renderable;

class CrateEntity : public Entity
{
public:
	CrateEntity(sf::Vector2f pos);
	virtual ~CrateEntity();
	
	virtual void update(double step);
	virtual EntityType getType() const override;
	
	void pickUp();
};

}}
