#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <memory>

namespace Zk {
namespace Game {

class Renderable;

enum class EntityType : int
{
	Unknown = 0,
	PlayerEntity,
	CrateEntity,
	MedKitEntity,
	GrenadePackEntity,
	LevelMeshEntity,
	SpawnerMeshEntity,
	MouseTrackEntity,
	BulletEntity,
	GrenadeEntity,
	CrosshairEntity,
	PlayerTrackEntity
};

class Entity
{
public:
	Entity(Renderable * vr, b2Body * pr);
	virtual ~Entity();

	virtual void update(double step) = 0;

	virtual sf::Vector2f getCenterPosition() const;

	std::weak_ptr<Renderable> getRenderable() const
	{ return visualRep; }
	inline b2Body * getBody() const
	{ return body; }

	inline bool wantsToBeDeleted() const
	{ return wannaDelete; }

	virtual EntityType getType() const;

protected:
	void setRenderable(Renderable * r);
	void setBody(b2Body * b);
	void markForDeletion();

private:
	std::shared_ptr<Renderable> visualRep;
	b2Body * body;

	bool wannaDelete;
};

}}
