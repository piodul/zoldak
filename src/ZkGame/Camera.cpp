#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <QtCore>

#include <algorithm>

#include "../ZkCommon/Constants.h"

#include "Camera.h"
#include "Entities/Entity.h"

using namespace Zk::Common;
using namespace Zk::Game;

//TODO: Udostępnić informacje o rozmiarze ekranu publicznie w innym miejscu
static const double SCREEN_WIDTH = 800.0 * Constants::METERS_PER_PIXEL;
static const double SCREEN_HEIGHT = 600.0 * Constants::METERS_PER_PIXEL;

std::vector<sf::View> Camera::getViews() const
{
	return computedViews;
}

void Camera::discardInvalidEntities()
{
	std::remove_if(
		trackedEntities.begin(), trackedEntities.end(),
		[&](std::weak_ptr<Entity> ent) -> bool
		{
			return ent.expired();
		}
	);
}

SplitScreenCamera::SplitScreenCamera(
	std::initializer_list<std::weak_ptr<Entity>> entities
)
{
	trackedEntities = entities;
	alignment = Alignment::Horizontal;
}

SplitScreenCamera::SplitScreenCamera(
	const std::vector<std::weak_ptr<Entity>> & entities
)
{
	trackedEntities = entities;
	alignment = Alignment::Horizontal;
}

SplitScreenCamera::~SplitScreenCamera()
{
	
}

void SplitScreenCamera::setupViews()
{
	discardInvalidEntities();
	computedViews.clear();
	
	sf::View view;
	
	if (trackedEntities.size() > 0)
	{
		int id = 0;
		float step = 1.f / (float)trackedEntities.size();
		for (std::weak_ptr<Entity> weakEnt : trackedEntities)
		{
			std::shared_ptr<Entity> ent = weakEnt.lock();
			float factor = (float)id * step;
			switch (alignment)
			{
			case Alignment::Horizontal:
				view.reset(sf::FloatRect(
					factor * (float)SCREEN_WIDTH,
					0.f,
					(factor + step) * (float)SCREEN_WIDTH,
					(float)SCREEN_HEIGHT
				));
				
				view.setViewport(sf::FloatRect(factor, 0.f, factor + step, 1.f));
				break;
				
			case Alignment::Vertical:
				view.reset(sf::FloatRect(
					0.f,
					factor * (float)SCREEN_HEIGHT,
					(float)SCREEN_WIDTH,
					(factor + step) * (float)SCREEN_HEIGHT
				));
				
				view.setViewport(sf::FloatRect(0.f, factor, 1.f, factor + step));
				break;
			}
			
			view.setCenter(ent->getCenterPosition());
			
			computedViews.push_back(view);
			
			id++;
		}
	}
	else
	{
		view.reset(
			sf::FloatRect(0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT)
		);
		
		view.setViewport(
			sf::FloatRect(0.f, 0.f, 1.f, 1.f)
		);
		
		computedViews.push_back(view);
	}
	
	// if (trackedEntities.size() > 0)
	// {
	// 	for (std::weak_ptr<Entity> weakEnt : trackedEntities)
	// 	{
	// 		//discardInvalidEntities gwarantuje nam,
	// 		//że jest to poprawny wskaźnik
	// 		std::shared_ptr<Entity> ent = weakEnt.lock();
			
	// 		sf::Vector2f pos = ent->getCenterPosition();
	// 	}
	// }
}
