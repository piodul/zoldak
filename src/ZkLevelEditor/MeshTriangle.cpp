#include "MeshTriangle.h"
#include "MeshTriangleNode.h"

#include <QtCore>
#include <QtGui>
#include <QDebug>

using namespace Zk::LevelEditor;

MeshTriangle::MeshTriangle(
	LevelView * lv,
	std::array<MeshTriangleNode*, 3> verts,
	QGraphicsItem * parent
)
	: QGraphicsPathItem(parent)
{
	parentView = lv;
	this->verts = verts;
	
	for (MeshTriangleNode * vert : verts)
	{
		connect(vert, SIGNAL(moved(MeshTriangleNode*, const QPointF&)),
			this, SLOT(updatePosition(MeshTriangleNode*, const QPointF&)));
		
		updatePosition(vert, vert->pos());
	}
	
	setBrush(QBrush(QColor(255, 127, 0)));
	setPen(QPen(Qt::transparent));
	setZValue(-1.0);
}

MeshTriangle::~MeshTriangle()
{
	
}

void MeshTriangle::updatePosition(MeshTriangleNode * mtn, const QPointF & pos)
{
	QPolygonF poly;
	for (MeshTriangleNode * vert : verts)
	{
		if (vert == mtn)
			poly << pos;
		else
			poly << vert->pos();
	}
	
	QPainterPath path;
	path.addPolygon(poly);
	setPath(path);
}
