#pragma once

#include <SFML/Graphics.hpp>
#include <QtCore>
#include <QtGui>

#include <array>

namespace Zk {
namespace Common {

struct triangleDesc_t
{
	std::array<qint16, 3> vert;
	std::array<QColor, 3> color;
};

QDataStream & operator<<(QDataStream & ds, const triangleDesc_t & td);
QDataStream & operator>>(QDataStream & ds, triangleDesc_t & td);

class LevelLayer
{
public:
	LevelLayer();
	~LevelLayer();

	void clear();

	void constructMesh(sf::VertexArray & varr) const;
	void constructOutline(sf::VertexArray & varr) const;

	const QVector<sf::Vertex> & getVertices() const;
	const QVector<triangleDesc_t> & getTriangleDescriptions() const;
	void setVertices(const QVector<sf::Vertex> & verts);
	void setTriangleDescriptions(const QVector<triangleDesc_t> & descs);

	void calculateTexCoords();

	friend QDataStream & operator<<(QDataStream & ds, const LevelLayer & ll);
	friend QDataStream & operator>>(QDataStream & ds, LevelLayer & ll);

private:
	QVector<sf::Vertex> verts;
	QVector<triangleDesc_t> descs;

};

class Level
{
public:
	Level();
	~Level();

	void clear();

	const QVector<LevelLayer*> & getLayers() const;
	const QVector<QColor> & getPalette() const;
	void setLayers(const QVector<LevelLayer*> & layers);
	void setPalette(const QVector<QColor> & colors);

	friend QDataStream & operator<<(QDataStream & ds, const Level & l);
	friend QDataStream & operator>>(QDataStream & ds, Level & l);

private:
	QVector<LevelLayer*> layers;
	QVector<QColor> palette;

};

}}
