#include "MeshTriangle.h"
#include "TriangleNode.h"

#include <QtCore>
#include <QtGui>
#include <QDebug>

using namespace Zk::LevelEditor;

MeshTriangle::MeshTriangle(
	LevelView * lv,
	std::array<TriangleNode*, 3> verts,
	QGraphicsItem * parent
)
	: QGraphicsPathItem(parent)
{
	parentView = lv;
	this->verts = verts;
	
	for (TriangleNode * vert : verts)
	{
		connect(vert, SIGNAL(moved(TriangleNode*, const QPointF&)),
			this, SLOT(updatePosition(TriangleNode*, const QPointF&)));
		
		updatePosition(vert, vert->pos());
	}
	
	setBrush(QBrush(QColor(255, 127, 0)));
	setPen(QPen(Qt::transparent));
	setZValue(-1.0);
}

MeshTriangle::~MeshTriangle()
{
	
}

void MeshTriangle::updatePosition(TriangleNode * tn, const QPointF & pos)
{
	QPolygonF poly;
	for (TriangleNode * vert : verts)
	{
		if (vert == tn)
			poly << pos;
		else
			poly << vert->pos();
	}
	
	QPainterPath path;
	path.addPolygon(poly);
	setPath(path);
}
