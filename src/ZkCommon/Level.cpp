#include <SFML/Graphics.hpp>

#include "Level.hpp"
#include "LibraryCast.hpp"

#include <QtCore>
#include <QtGui>

#include <map>
#include <utility>

using namespace Zk::Common;

LevelLayer::LevelLayer()
{

}

LevelLayer::~LevelLayer()
{

}

void LevelLayer::clear()
{
	verts.clear();
	descs.clear();
}

void LevelLayer::constructMesh(sf::VertexArray & varr) const
{
	varr.clear();
	varr.setPrimitiveType(sf::Triangles);

	for (const triangleDesc_t & td : descs)
	{
		for (int i : { 0, 1, 2 })
		{
			sf::Vertex vert = verts[td.vert[i]];
			QColor c = td.color[i];
			vert.color = lib_cast<sf::Color>(c);
			varr.append(vert);
		}
	}
}

void LevelLayer::constructOutline(sf::VertexArray & varr) const
{
	varr.clear();
	varr.setPrimitiveType(sf::Lines);

	std::map<std::pair<int, int>, int> hitcount;

	static const std::pair<int, int> edges[] = {
		{ 0, 1 },
		{ 1, 2 },
		{ 2, 0 }
	};

	for (const std::pair<int, int> & e : edges)
	{
		for (const triangleDesc_t & td : descs)
		{
			int v1 = td.vert[e.first];
			int v2 = td.vert[e.second];

			if (v1 > v2)
				std::swap(v1, v2);

			hitcount[{ v1, v2 }]++;
		}
	}

	for (auto p : hitcount)
	{
		if (p.second == 1)
		{
			auto edge = p.first;

			varr.append(verts[edge.first]);
			varr.append(verts[edge.second]);
		}
	}
}

const QVector<sf::Vertex> & LevelLayer::getVertices() const
{
	return verts;
}

const QVector<triangleDesc_t> & LevelLayer::getTriangleDescriptions() const
{
	return descs;
}

void LevelLayer::setVertices(const QVector<sf::Vertex> & verts)
{
	this->verts = verts;
}

void LevelLayer::setTriangleDescriptions(const QVector<triangleDesc_t> & descs)
{
	this->descs = descs;
}

void LevelLayer::calculateTexCoords()
{
	//TBI
}

Level::Level()
{

}

Level::~Level()
{
	for (LevelLayer * ll : layers)
		delete ll;
}

void Level::clear()
{
	layers.clear();
	palette.clear();
}

void Level::setLayers(const QVector<LevelLayer*> & layers)
{
	this->layers = layers;
}

void Level::setPalette(const QVector<QColor> & colors)
{
	this->palette = colors;
}

const QVector<LevelLayer*> & Level::getLayers() const
{
	return layers;
}

const QVector<QColor> & Level::getPalette() const
{
	return palette;
}

QDataStream & Zk::Common::operator<<(QDataStream & ds, const triangleDesc_t & td)
{
	ds << td.vert[0];
	ds << td.vert[1];
	ds << td.vert[2];

	ds << td.color[0];
	ds << td.color[1];
	ds << td.color[2];

	return ds;
}

QDataStream & Zk::Common::operator>>(QDataStream & ds, triangleDesc_t & td)
{
	ds >> td.vert[0];
	ds >> td.vert[1];
	ds >> td.vert[2];

	ds >> td.color[0];
	ds >> td.color[1];
	ds >> td.color[2];

	return ds;
}

QDataStream & Zk::Common::operator<<(QDataStream & ds, const LevelLayer & ll)
{
	ds << (qint16)ll.verts.size();
	for (const sf::Vertex & vert : ll.verts)
		ds << vert.position.x << vert.position.y;

	ds << (qint16)ll.descs.size();
	for (const triangleDesc_t & td : ll.descs)
		ds << td;

	return ds;
}

QDataStream & Zk::Common::operator>>(QDataStream & ds, LevelLayer & ll)
{
	qint16 nverts;
	ds >> nverts;
	ll.verts.reserve((int)nverts);
	for (int i = 0; i < nverts; i++)
	{
		float x, y;
		ds >> x >> y;
		ll.verts.push_back(sf::Vertex(sf::Vector2f(x, y)));
	}

	qint16 ndescs;
	ds >> ndescs;
	ll.descs.reserve((int)ndescs);
	for (int i = 0; i < ndescs; i++)
	{
		triangleDesc_t td;
		ds >> td;
		ll.descs.push_back(td);
	}

	return ds;
}

QDataStream & Zk::Common::operator<<(QDataStream & ds, const Level & l)
{
	ds << (qint8)l.layers.size();
	for (const LevelLayer * ll : l.layers)
		ds << *ll;

	ds << (qint16)l.palette.size();
	for (const QColor & color : l.palette)
		ds << color;

	return ds;
}

QDataStream & Zk::Common::operator>>(QDataStream & ds, Level & l)
{
	qint8 nlayers;
	ds >> nlayers;
	l.layers.reserve(nlayers);
	for (int i = 0; i < nlayers; i++)
	{
		LevelLayer * ll = new LevelLayer();
		ds >> *ll;
		l.layers.push_back(ll);
	}

	qint16 ncolors;
	ds >> ncolors;
	l.palette.reserve((int)ncolors);
	for (int i = 0; i < ncolors; i++)
	{
		QColor color;
		ds >> color;
		l.palette.push_back(color);
	}

	return ds;
}
