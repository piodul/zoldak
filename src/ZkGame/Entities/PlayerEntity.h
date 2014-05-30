#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Entity.h"

namespace Zk {
namespace Game {

class Renderable;

class PlayerEntity : public Entity
{
public:
	PlayerEntity();
	virtual ~PlayerEntity();
	
	virtual void update(double step);
	
private:
	
};

}}
