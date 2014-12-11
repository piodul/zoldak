#include <SFML/Graphics.hpp>

#include <cmath>

#include <random>

#include "../ZkCommon/Level.hpp"

#include "SpawnerMesh.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

static sf::Vector2f randomPointInTriangle(std::array<sf::Vector2f, 3> verts);
static float triangleArea(std::array<sf::Vector2f, 3> verts);

SpawnerMesh::SpawnerMesh()
{

}

SpawnerMesh::SpawnerMesh(const LevelLayer * ll)
{
	ll->constructMesh(varr);
}

sf::Vector2f SpawnerMesh::pickSpawnLocation() const
{
	static std::random_device rd;
	static std::default_random_engine dre(rd());

	//Liczymy pole
	float field = 0.f;
	for (int i = 0; i < (int)varr.getVertexCount(); i += 3)
		field += triangleArea({
			varr[i + 0].position,
			varr[i + 1].position,
			varr[i + 2].position
		});

	//Losujemy trójkąt
	std::uniform_real_distribution<float> dis(0, field);
	float t = dis(dre);
	field = 0.f;

	for (int i = 0; i < (int)varr.getVertexCount(); i += 3)
	{
		field += triangleArea({
			varr[i + 0].position,
			varr[i + 1].position,
			varr[i + 2].position
		});

		if (field >= t)
			return randomPointInTriangle({
				varr[i + 0].position,
				varr[i + 1].position,
				varr[i + 2].position
			});
	}

	//Justin Case
	return sf::Vector2f(0.f, 0.f);
}

sf::Vector2f randomPointInTriangle(std::array<sf::Vector2f, 3> verts)
{
	static std::random_device rd;
	static std::default_random_engine dre(rd());
	static std::uniform_real_distribution<float> dis(0, 1);

	float u = dis(dre), v = dis(dre);

	if (u + v > 1.f)
	{
		u = 1.f - u;
		v = 1.f - v;
	}

	return verts[0] + u * (verts[1] - verts[0]) + v * (verts[2] - verts[0]);
}

float triangleArea(std::array<sf::Vector2f, 3> verts)
{
	sf::Vector2f v1 = verts[1] - verts[0];
	sf::Vector2f v2 = verts[2] - verts[0];

	return fabs(v1.x * v2.y - v2.x * v1.y) * 0.5f;
}
