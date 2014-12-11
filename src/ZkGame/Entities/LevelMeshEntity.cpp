#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <algorithm>
#include <limits>
#include <map>

#include "../../ZkCommon/Constants.hpp"
#include "../../ZkCommon/LibraryCast.hpp"
#include "../../ZkCommon/Level.hpp"

#include "LevelMeshEntity.hpp"
#include "Entity.hpp"
#include "../Game.hpp"
#include "../GameSystem.hpp"
#include "../Renderables/Renderable.hpp"
#include "../Renderables/MeshRenderable.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

static b2Body * createLevelLayerCollisionMesh(const LevelLayer * ll);

LevelMeshEntity::LevelMeshEntity(const LevelLayer * ll, LayerType lt)
	: Entity(nullptr, nullptr)
{
	this->ll = ll;
	this->lt = lt;

	sf::VertexArray varr;
	ll->constructMesh(varr);

	Renderable * r = new MeshRenderable(
		getLayerNameByType(lt),
		varr
	);
	setRenderable(r);

	if (lt == LayerType::MIDGROUND)
	{
		b2Body * body = createLevelLayerCollisionMesh(ll);
		body->SetUserData((void*)this);
		setBody(body);
	}
}

LevelMeshEntity::~LevelMeshEntity()
{

}

void LevelMeshEntity::update(double step)
{

}

EntityType LevelMeshEntity::getType() const
{
	return EntityType::LevelMeshEntity;
}

static b2Body * createLevelLayerCollisionMesh(const LevelLayer * ll)
{
	//Ta funkcja zakłada, że wszystkie wierzchołki zewnętrzne mają stopień 2

	b2World & world = Game::getInstance()->getPhysicsSystem().getWorld();

	const QVector<sf::Vertex> & verts = ll->getVertices();
	const QVector<triangleDesc_t> & tris = ll->getTriangleDescriptions();

	std::map<std::pair<int, int>, int> edges;

	//Dla każdej krawędzi liczymy ilość trójkątów stykających się z nią
	//Robimy podwójne krawędzie aby łatwiej było po nich potem przechodzić
	for (triangleDesc_t t : tris)
	{
		edges[std::pair<int, int>(t.vert[0], t.vert[1])]++;
		edges[std::pair<int, int>(t.vert[1], t.vert[0])]++;

		edges[std::pair<int, int>(t.vert[0], t.vert[2])]++;
		edges[std::pair<int, int>(t.vert[2], t.vert[0])]++;

		edges[std::pair<int, int>(t.vert[1], t.vert[2])]++;
		edges[std::pair<int, int>(t.vert[2], t.vert[1])]++;
	}

	//Wywalamy wszystkie krawędzie poza zewnętrznymi

	//Ermagerd, remove_if nie działa dla map...
	for (auto it = edges.begin(); it != edges.end();)
	{
		if (it->second != 1)
			edges.erase(it++);
		else
			it++;
	}

	//Tworzymy ciało
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.userData = nullptr;

	b2Body * body = world.CreateBody(&bodyDef);

	//Znajdujemy i przekształcamy cykle na reprezentację Box2D-ową
	while (edges.size() > 0)
	{
		int firstVert = edges.begin()->first.first;
		int currVert = firstVert;

		QVector<b2Vec2> points;

		do
		{
			b2Vec2 pos = lib_cast<b2Vec2>(verts[currVert].position);
			points.push_back(pos);

			//Wybieramy dowolne połączenie z currVert
			auto it = edges.lower_bound(
				std::make_pair(currVert, std::numeric_limits<int>::min())
			);

			std::pair<int, int> e = it->first;

			//Usuwamy je (obustronnie)
			edges.erase(e);
			edges.erase(std::make_pair(e.second, e.first));

			//Przechodzimy do następnego wierzchołka
			currVert = e.second;

		}	while (currVert != firstVert);

		//Tworzymy łańcuch z punktów
		b2ChainShape chain;
		chain.CreateLoop(&points[0], points.size());

		b2FixtureDef chainFixtureDef;
		chainFixtureDef.shape = &chain;
		body->CreateFixture(&chainFixtureDef);
	}

	return body;
}
