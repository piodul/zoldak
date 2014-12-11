#pragma once

#include <SFML/Graphics.hpp>

namespace Zk {

namespace Common { class LevelLayer; }
namespace Game {

///Pomocnicza klasa do wybierania losowego punktu z mesh-u.
class SpawnerMesh
{
public:
	///Konstruuje pusty SpawnerMesh.
	SpawnerMesh();

	///Konstruuje SpawnerMesh na podstawie warstwy poziomu.
	SpawnerMesh(const Common::LevelLayer * ll);

	///Wybiera losowy punkt z mesh-u.
	sf::Vector2f pickSpawnLocation() const;

private:
	sf::VertexArray varr;
};

}}
