#include <SFML/Graphics.hpp>

#include "Level.h"

#include <QtCore>
#include <QtGui>

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
		varr.append(verts[td.vert[0]]);
		varr.append(verts[td.vert[1]]);
		varr.append(verts[td.vert[2]]);
	}
}

void LevelLayer::setVertices(const std::vector<sf::Vertex> & verts)
{
	this->verts = verts;
}

const std::vector<sf::Vertex> & LevelLayer::getVertices() const
{
	return verts;
}

void LevelLayer::setTriangleDescriptions(const std::vector<triangleDesc_t> & descs)
{
	this->descs = descs;
}

const std::vector<triangleDesc_t> & LevelLayer::getTriangleDescriptions() const
{
	return descs;
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
	
}

std::vector<LevelLayer*> & Level::getLayers()
{
	return layers;
}

QDataStream & Zk::Common::operator<<(QDataStream & ds, const triangleDesc_t & td)
{
	ds << td.vert[0];
	ds << td.vert[1];
	ds << td.vert[2];
	
	return ds;
}

QDataStream & Zk::Common::operator>>(QDataStream & ds, triangleDesc_t & td)
{
	ds >> td.vert[0];
	ds >> td.vert[1];
	ds >> td.vert[2];
	
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
	
	return ds;
}
